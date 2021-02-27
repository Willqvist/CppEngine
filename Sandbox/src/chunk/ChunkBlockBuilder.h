//
// Created by Gerry on 2020-09-08.
//

#ifndef CPPMC_CHUNKBLOCKBUILDER_H
#define CPPMC_CHUNKBLOCKBUILDER_H


#include "Chunk.h"
#include "../components/ChunkComponent.h"
#include <pipeline/PipelineObject.h>
#include <threading/ThreadPool.h>
class ChunkBlockBuilder : public PipelineObject<Ref<ChunkComponent>,Ref<ChunkComponent>> {
public:
    static Ref<ChunkBlockBuilder>& instance() {
        static Ref<ChunkBlockBuilder> instance {new ChunkBlockBuilder()};
        return instance;
    }

    void generate(const Ref<Chunk>& chunk) {
        std::srand(23224);
        for(int x = 0; x < CHUNK_WIDTH; x++) {
            for(int z = 0; z < CHUNK_DEPTH; z++) {
                for(int y = 0; y < CHUNK_HEIGHT; y++) {
                    if(std::rand() % 100 > 90 && y < 120)
                        chunk->setBlock(x,y,z,Block::DIRT);
                    else
                        chunk->setBlock(x,y,z,Block::AIR);
                }
            }
        }
    }

    void threads(int num) {
        if(threadPool != nullptr) {
            delete threadPool;
        }
        threadPool = new ThreadPool<Ref<ChunkComponent>>(num);
    }

    ChunkBlockBuilder(ChunkBlockBuilder const&) = delete;
    void operator=(ChunkBlockBuilder const&)  = delete;

protected:
    void onInsert(Ref<ChunkComponent> &val) override {
        threadPool->enqueue(
        [this](Ref<ChunkComponent>& c, int threadId) {
            this->generate(c->getChunk());
            send(c);
        }, val);
    }

private:
    ChunkBlockBuilder() {}
    ThreadPool<Ref<ChunkComponent>>* threadPool = nullptr;
};


#endif //CPPMC_CHUNKBLOCKBUILDER_H
