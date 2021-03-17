//
// Created by Gerry on 2021-03-16.
//

#include "../components/ChunkComponent.h"
#include "ChunkModelBuilder.h"
#include <glm/gtx/norm.hpp>
#include "tools/Tools.h"
#include <rendering/VertexArray.h>
#include <threading/MainThread.h>
#include <scene/components/Transform.h>

ChunkModelBuilder::ChunkModelBuilder() {

}

Ref<ChunkModelBuilder> &VoxEng::ChunkModelBuilder::instance() {
    static Ref<ChunkModelBuilder> instance {new ChunkModelBuilder()};
    return instance;
}

void ChunkModelBuilder::threads(int num) {
    if(threadPool != nullptr) {
        delete threadPool;
    }
    threadPool = new ThreadPool<Ref<ChunkComponent>>(num);
}

void ChunkModelBuilder::wow(std::vector<float> &uvData) {
    uvData.push_back(0);
    uvData.push_back(1);

    uvData.push_back(1);
    uvData.push_back(1);

    uvData.push_back(1);
    uvData.push_back(0);

    uvData.push_back(0);
    uvData.push_back(0);
}

void ChunkModelBuilder::follow(Entity &following){
    this->following = following;

    threadPool->select([this](Ref<ChunkComponent>& c)
       {
           Transform& trans = this->following.getComponent<Transform>();
           glm::vec2 pos = c->worldPosition();
           glm::vec3 pPos = trans.position();
           glm::vec2 pPos2 = glm::vec2{ pPos.x,pPos.z };

           return distance2(pos, pPos2);
       });

}

void ChunkModelBuilder::onInsert(Ref<ChunkComponent> &val) {
    threadPool->enqueue(
    [this](Ref<ChunkComponent>& c, int threadId) {
        this->buildingChunk(c,threadId);
    }
    , val);
}

void ChunkModelBuilder::generate(Chunk &c, GeneratePointers *ptrs){
    int vertexIndex = 0, uvIndex = 0,indiciesIndex = 0;
    int index = 0;
    for(int y = 0; y <= c.highestY; y++) {
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

GeneratePointers ChunkModelBuilder::getPointers(int pool) {
    float* data = vertexPool.GetIndex(pool);
    float* uv = uvPool.GetIndex(pool);
    unsigned int* indicies = indiciesPool.GetIndex(pool);
    return { data,uv,indicies,0,0,0 };
}

void ChunkModelBuilder::returnData(GeneratePointers &ptrs) {
    //vertexPool.Return(ptrs.vertices);
    //uvPool.Return(ptrs.uvs);
    //indiciesPool.Return(ptrs.indicies);
}

void ChunkModelBuilder::buildingChunk(Ref<ChunkComponent> &c, int threadId) {
    int t = getTime();
    threadPool->freeze(threadId);
    GeneratePointers ptrs = getPointers(threadId);
    generate(*c->getChunk(), &ptrs);
    MainThreadDataRet* mainThreadData = new MainThreadDataRet();
    mainThreadData->ptrs = ptrs;
    mainThreadData->queueData = c;
    mainThreadData->id = threadId;
    printf("It took: %d ms to generate chunk\n",getTime()-t);
    MainThread::enqueue(mainThreadData,[&](void* mainData){
        MainThreadDataRet* retData = static_cast<MainThreadDataRet*>(mainData);
        GeneratePointers& ptrs = retData->ptrs;
        Ref<VertexArray> vertexArray = VertexArray::create();
        Ref<ArrayBuffer> buffer = ArrayBuffer::create(ptrs.vertices, ptrs.vertexSize * sizeof(float));
        Ref<ArrayBuffer> uvBuffer = ArrayBuffer::create(ptrs.uvs, ptrs.uvSize * sizeof(float));
        Ref<IndexBuffer> ibuffer = IndexBuffer::create(ptrs.indicies,
                                                       ptrs.indexSize * sizeof(unsigned int));
        returnData(ptrs);
        threadPool->unfreeze(retData->id);
        buffer->setLayout(layout);
        uvBuffer->setLayout(uvLayout);
        vertexArray->addIndexBuffer(ibuffer);
        vertexArray->addBuffer(buffer);
        vertexArray->addBuffer(uvBuffer);
        ChunkModelBuilderData dat;
        dat.data = vertexArray;
        dat.chunkComp = retData->queueData;
        send(dat);
        retData->queueData->getChunk()->setDirty(false);
        delete retData;
    });
}
