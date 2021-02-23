

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
        Ref<IChunk> c = this->chunkCreator->createChunk();
    }
private:
    Scope<IChunkCreator> chunkCreator;
    std::vector<Ref<IChunk>> chunks;
};


#endif //CPPMC_WORLD_H
