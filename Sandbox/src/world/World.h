

//
// Created by Gerry on 2021-02-23.
//

#ifndef CPPMC_WORLD_H
#define CPPMC_WORLD_H
#include "../chunk/IChunk.h"
#include "IChunkCreator.h"
using namespace VoxEng;

class World {
public:
    World(Scope<IChunkCreator>& chunkCreator) : chunkCreator(std::move(chunkCreator)) {
        for(int i = 0; i < 60; i++) {
            for(int j = 0; j < 60; j++) {
                this->chunkCreator->createChunk(i,j);
            }
        }
    }
private:
    Scope<IChunkCreator> chunkCreator;
    std::vector<Ref<IChunk>> chunks;
};


#endif //CPPMC_WORLD_H
