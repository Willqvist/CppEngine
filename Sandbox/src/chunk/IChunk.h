//
// Created by Gerry on 2021-02-23.
//

#ifndef CPPMC_ICHUNK_H
#define CPPMC_ICHUNK_H
#include "Block.h"
#include "core/Core.h"

using namespace BG;

class IChunk {
public:
    virtual Block getBlock(int x, int y, int z) = 0;
    virtual void setBlock(int x, int y, int z, Block& block) = 0;
    virtual Block* getBlocks() = 0;
    virtual bool isDirty() = 0;
    virtual void setNeighbor(VoxEng::Ref<IChunk> chunk, int neigh) = 0;
    virtual bool hasNeighbor(int neigh) = 0;
};

#endif //CPPMC_ICHUNK_H
