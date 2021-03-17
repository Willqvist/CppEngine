//
// Created by Gerry on 2021-03-16.
//
#include "ChunkBlockBuilder.h"
#include <glm/gtc/noise.hpp>
#include "../components/ChunkComponent.h"
#include <glm/gtx/norm.hpp>
#include <scene/components/Transform.h>
void ChunkBlockBuilder::follow(Entity &following)
{
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

void ChunkBlockBuilder::generate(const Ref<Chunk> &chunk, glm::vec2 worldPos) {
    std::srand(23224);
    for(int x = 0; x < CHUNK_WIDTH; x++) {
        for(int z = 0; z < CHUNK_DEPTH; z++) {
            int height = simplex(glm::vec2((worldPos.x+x)/32.0f,(worldPos.y+z)/32.0f))*8+120;
            for(int y = 0; y < CHUNK_HEIGHT; y++) {
                //printf("wew: %f \n",glm::simplex(glm::vec2(x/16.0f,z/16.0f)));
                if(height > y)
                    chunk->setBlock(x,y,z,Block::DIRT);
                else
                    chunk->setBlock(x,y,z,Block::AIR);
            }
        }
    }
}

void ChunkBlockBuilder::threads(int num) {
    if(threadPool != nullptr) {
        delete threadPool;
    }
    threadPool = new ThreadPool<Ref<ChunkComponent>>(num);
}

void ChunkBlockBuilder::onInsert(Ref<ChunkComponent> &val) {
    //if(!val->getChunk()->isDirty())
    //return;
    threadPool->enqueue(
            [this](Ref<ChunkComponent>& c, int threadId) {
                this->generate(c->getChunk(),c->worldPosition());
                c->getChunk()->setDirty(false);
                send(c);
            }, val);
}

Ref<ChunkBlockBuilder> &ChunkBlockBuilder::instance() {
    static Ref<ChunkBlockBuilder> instance {new ChunkBlockBuilder()};
    return instance;
}