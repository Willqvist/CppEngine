//
// Created by Gerry on 2020-09-08.
//

#ifndef CPPMC_CHUNKMODELBUILDER_H
#define CPPMC_CHUNKMODELBUILDER_H


#include <tools/ThreadPool.h>
#include <rendering/VertexArray.h>
#include "Chunk.h"
#include "tools/DataPool.h"

namespace VoxEng {
    class ChunkModelBuilder {
    public:
        static void threads(int num) {
            if(threadPool != nullptr) {
                delete threadPool;
            }
            threadPool = new ThreadPool<Chunk>(num);
        }

        static void build(Chunk &c) {
            threadPool->enqueue(buildingChunk, c);
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
        static Ref<VertexArray> generate(Ref<Chunk>& c){
            return generate(*c);
        }
        static Ref<VertexArray> generate(Chunk& c){
            Ref<VertexArray> vertexArray = VertexArray::create();

            std::vector<float> data = std::vector<float>();
            std::vector<float> uvData = std::vector<float>();
            std::vector<unsigned int> indicies = std::vector<unsigned int>();
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
                                faceData.move(x, y, z, data);
                                faceData.indexBase(index, indicies);
                                uvFaceData.fill(uvData);
                                index += 4;
                            }

                            if(!c.getBlock(x+1,y,z).isOpaque(Sides::LEFT)) {
                                FaceData  faceData = BlockFaceData::getData(b, BlockFace::RIGHT);
                                UVData uvFaceData = BlockFaceData::getUvData(b,BlockFace::RIGHT);
                                faceData.move(x, y, z, data);
                                faceData.indexBase(index, indicies);
                                uvFaceData.fill(uvData);
                                index += 4;
                            }

                            if(!c.getBlock(x,y,z-1).isOpaque(Sides::BACK)) {
                                FaceData faceData = BlockFaceData::getData(b, BlockFace::FRONT);
                                UVData uvFaceData = BlockFaceData::getUvData(b,BlockFace::FRONT);
                                faceData.move(x, y, z, data);
                                faceData.indexBase(index, indicies);
                                uvFaceData.fill(uvData);
                                index += 4;
                            }

                            if(!c.getBlock(x,y,z+1).isOpaque(Sides::FRONT)) {
                                FaceData faceData = BlockFaceData::getData(b, BlockFace::BACK);
                                UVData uvFaceData = BlockFaceData::getUvData(b,BlockFace::BACK);
                                faceData.move(x, y, z, data);
                                faceData.indexBase(index, indicies);
                                uvFaceData.fill(uvData);
                                index += 4;
                            }

                            if(!c.getBlock(x,y+1,z).isOpaque(Sides::BOTTOM)) {
                                FaceData faceData = BlockFaceData::getData(b, BlockFace::TOP);
                                UVData uvFaceData = BlockFaceData::getUvData(b,BlockFace::TOP);
                                faceData.move(x, y, z, data);
                                faceData.indexBase(index, indicies);
                                uvFaceData.fill(uvData);
                                index += 4;
                            }

                            if(!c.getBlock(x,y-1,z).isOpaque(Sides::TOP)) {
                                FaceData faceData = BlockFaceData::getData(b, BlockFace::BOTTOM);
                                UVData uvFaceData = BlockFaceData::getUvData(b,BlockFace::BOTTOM);
                                faceData.move(x, y, z, data);
                                faceData.indexBase(index, indicies);
                                uvFaceData.fill(uvData);
                                index += 4;
                            }
                        }
                    }
                }
            }

            Ref<ArrayBuffer> buffer = ArrayBuffer::create(data.data(),data.size()* sizeof(float));
            Ref<ArrayBuffer> uvBuffer = ArrayBuffer::create(uvData.data(),uvData.size()* sizeof(float));
            Ref<IndexBuffer> ibuffer = IndexBuffer::create(indicies.data(),indicies.size() * sizeof(unsigned int));
            buffer->setLayout(layout);
            uvBuffer->setLayout(uvLayout);
            vertexArray->addIndexBuffer(ibuffer);
            vertexArray->addBuffer(buffer);
            vertexArray->addBuffer(uvBuffer);
            return vertexArray;
        }

    private:
        static const inline BufferLayout layout = BufferLayout({
            BufferElement(ElementType::float3)
        });

        static const inline BufferLayout uvLayout = BufferLayout({
            BufferElement(ElementType::float2)
        });
        static void buildingChunk(Chunk& c) {
            /*
            int size = sizeof(c.getBlocks())*8;
            float* data = vertexPool.Rent(size);
            vertexPool.Return(data,size);
             */
        }

        static inline DataPool<float, 10000 * 5> vertexPool;
        static inline ThreadPool<Chunk>* threadPool;
    };
}

#endif //CPPMC_CHUNKMODELBUILDER_H
