//
// Created by Gerry on 2020-09-08.
//

#ifndef CPPMC_CHUNK_H
#define CPPMC_CHUNK_H

#include <vector>
#include <scene/Entity.hpp>

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 255
#define CHUNK_DEPTH 16
using namespace VoxEng;
class Chunk {
public:
    unsigned short* getBlocks() {
        return blocks;
    }
private:
    unsigned short blocks[CHUNK_WIDTH*CHUNK_HEIGHT*CHUNK_DEPTH];
    std::vector<Entity> entities;
};


#endif //CPPMC_CHUNK_H
