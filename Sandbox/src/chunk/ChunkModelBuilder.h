//
// Created by Gerry on 2020-09-08.
//

#ifndef CPPMC_CHUNKMODELBUILDER_H
#define CPPMC_CHUNKMODELBUILDER_H


#include <threading/ThreadPool.h>
#include <rendering/VertexArray.h>
#include <threading/MainThread.h>
#include <pipeline/PipelineObject.h>
#include "Chunk.h"
#include "tools/DataPool.h"
#include "tools/Tools.h"
#include "../components/ChunkComponent.h"

struct GeneratedData {
    std::vector<float> data, uvData;
    std::vector<unsigned int> indicies;
};

using BuildCallback = std::function<void(Ref<VertexArray>& vao)>;

struct ChunkQueueData {
    Ref<ChunkComponent> chunk;
};

struct GeneratePointers {
    float* vertices;
    float* uvs;
    unsigned int* indicies;
    int vertexSize, uvSize, indexSize;
};


struct MainThreadDataRet {
    Ref<ChunkComponent> queueData;
    GeneratePointers ptrs;
};

struct ChunkModelBuilderData {
    Ref<ChunkComponent> chunkComp;
    Ref<VertexArray> data;
};

namespace VoxEng {
    class ChunkModelBuilder : public PipelineObject<Ref<ChunkComponent>,ChunkModelBuilderData> {
    public:

        static Ref<ChunkModelBuilder>& instance() {
            static Ref<ChunkModelBuilder> instance {new ChunkModelBuilder()};
            return instance;
        }

        void threads(int num) {
            if(threadPool != nullptr) {
                delete threadPool;
            }
            threadPool = new ThreadPool<Ref<ChunkComponent>>(num);
        }

        static void wow(std::vector<float>& uvData) {
            uvData.push_back(0);
            uvData.push_back(1);

            uvData.push_back(1);
            uvData.push_back(1);

            uvData.push_back(1);
            uvData.push_back(0);

            uvData.push_back(0);
            uvData.push_back(0);
        }
        ChunkModelBuilder(ChunkModelBuilder const&) = delete;
        void operator=(ChunkModelBuilder const&)  = delete;

    private:

    protected:
        void onInsert(Ref<ChunkComponent> &val) override {
            threadPool->enqueue(
                    [this](Ref<ChunkComponent>& c, int threadId) {
                        this->buildingChunk(c,threadId);
                    }
                    , val);
        }

    private:

        ChunkModelBuilder() {}
        void generate(Chunk& c,GeneratePointers* ptrs){
            int vertexIndex = 0, uvIndex = 0,indiciesIndex = 0;
            int index = 0;
            for(int y = 0; y < c.highestY; y++) {
                if(c.opaqueBlocksPerLayer[y] == 0)
                    continue;

                for(int x  = 0; x < CHUNK_WIDTH; x++) {
                    for(int z = 0; z < CHUNK_DEPTH; z++) {
                        Block b = c.getBlock(x,y,z);
                        Block neigh;
                        if(!b.isFullyTransparent()) {

                            if(!c.getBlock(x-1,y,z).isOpaque(Sides::RIGHT)) {
                                FaceData faceData = BlockFaceData::getData(b, BlockFace::LEFT);
                                UVData uvFaceData = BlockFaceData::getUvData(b,BlockFace::LEFT);
                                faceData.move(x, y, z, ptrs->vertices,&vertexIndex);
                                faceData.indexBase(index, ptrs->indicies,&indiciesIndex);
                                uvFaceData.fill(ptrs->uvs,&uvIndex);
                                index += 4;
                            }

                            if(!c.getBlock(x+1,y,z).isOpaque(Sides::LEFT)) {
                                FaceData  faceData = BlockFaceData::getData(b, BlockFace::RIGHT);
                                UVData uvFaceData = BlockFaceData::getUvData(b,BlockFace::RIGHT);
                                faceData.move(x, y, z, ptrs->vertices,&vertexIndex);
                                faceData.indexBase(index, ptrs->indicies,&indiciesIndex);
                                uvFaceData.fill(ptrs->uvs,&uvIndex);
                                index += 4;
                            }

                            if(!c.getBlock(x,y,z-1).isOpaque(Sides::BACK)) {
                                FaceData faceData = BlockFaceData::getData(b, BlockFace::FRONT);
                                UVData uvFaceData = BlockFaceData::getUvData(b,BlockFace::FRONT);
                                faceData.move(x, y, z, ptrs->vertices,&vertexIndex);
                                faceData.indexBase(index, ptrs->indicies,&indiciesIndex);
                                uvFaceData.fill(ptrs->uvs,&uvIndex);
                                index += 4;
                            }

                            if(!c.getBlock(x,y,z+1).isOpaque(Sides::FRONT)) {
                                FaceData faceData = BlockFaceData::getData(b, BlockFace::BACK);
                                UVData uvFaceData = BlockFaceData::getUvData(b,BlockFace::BACK);
                                faceData.move(x, y, z, ptrs->vertices,&vertexIndex);
                                faceData.indexBase(index, ptrs->indicies,&indiciesIndex);
                                uvFaceData.fill(ptrs->uvs,&uvIndex);
                                index += 4;
                            }

                            if(!c.getBlock(x,y+1,z).isOpaque(Sides::BOTTOM)) {
                                FaceData faceData = BlockFaceData::getData(b, BlockFace::TOP);
                                UVData uvFaceData = BlockFaceData::getUvData(b,BlockFace::TOP);
                                faceData.move(x, y, z, ptrs->vertices,&vertexIndex);
                                faceData.indexBase(index, ptrs->indicies,&indiciesIndex);
                                uvFaceData.fill(ptrs->uvs,&uvIndex);
                                index += 4;
                            }

                            if(!c.getBlock(x,y-1,z).isOpaque(Sides::TOP)) {
                                FaceData faceData = BlockFaceData::getData(b, BlockFace::BOTTOM);
                                UVData uvFaceData = BlockFaceData::getUvData(b,BlockFace::BOTTOM);
                                faceData.move(x, y, z, ptrs->vertices,&vertexIndex);
                                faceData.indexBase(index, ptrs->indicies,&indiciesIndex);
                                uvFaceData.fill(ptrs->uvs,&uvIndex);
                                index += 4;
                            }
                        }
                    }
                }
            }
            ptrs->indexSize = indiciesIndex;
            ptrs->vertexSize = vertexIndex;
            ptrs->uvSize = uvIndex;
        }

        const BufferLayout layout = BufferLayout({
            BufferElement(ElementType::float3)
        });

        const BufferLayout uvLayout = BufferLayout({
            BufferElement(ElementType::float2)
        });

        GeneratePointers getPointers(int pool) {
            float* data = vertexPool.GetIndex(pool);
            float* uv = uvPool.GetIndex(pool);
            unsigned int* indicies = indiciesPool.GetIndex(pool);
            return { data,uv,indicies,0,0,0 };
        }

        void returnData(GeneratePointers& ptrs) {
            //vertexPool.Return(ptrs.vertices);
            //uvPool.Return(ptrs.uvs);
            //indiciesPool.Return(ptrs.indicies);
        }

        void buildingChunk(Ref<ChunkComponent>& c, int threadId) {
                GeneratePointers ptrs = getPointers(threadId);
                generate(*c->getChunk(), &ptrs);
                MainThreadDataRet* mainThreadData = new MainThreadDataRet();
                mainThreadData->ptrs = ptrs;
                mainThreadData->queueData = c;

                MainThread::enqueue(mainThreadData,[&](void* mainData){
                    MainThreadDataRet* retData = static_cast<MainThreadDataRet*>(mainData);
                    GeneratePointers& ptrs = retData->ptrs;
                    Ref<VertexArray> vertexArray = VertexArray::create();
                    Ref<ArrayBuffer> buffer = ArrayBuffer::create(ptrs.vertices, ptrs.vertexSize * sizeof(float));
                    Ref<ArrayBuffer> uvBuffer = ArrayBuffer::create(ptrs.uvs, ptrs.uvSize * sizeof(float));
                    Ref<IndexBuffer> ibuffer = IndexBuffer::create(ptrs.indicies,
                        ptrs.indexSize * sizeof(unsigned int));
                    returnData(ptrs);
                    buffer->setLayout(layout);
                    uvBuffer->setLayout(uvLayout);
                    vertexArray->addIndexBuffer(ibuffer);
                    vertexArray->addBuffer(buffer);
                    vertexArray->addBuffer(uvBuffer);
                    ChunkModelBuilderData dat;
                    dat.data = vertexArray;
                    dat.chunkComp = retData->queueData;
                    send(dat);
                    delete retData;
                });
        }

        DataPool<float, 200000,10> vertexPool;
        DataPool<float, 200000,10> uvPool;
        DataPool<unsigned int, 150000,10> indiciesPool;
        ThreadPool<Ref<ChunkComponent>>* threadPool = nullptr;
    };
}

#endif //CPPMC_CHUNKMODELBUILDER_H
