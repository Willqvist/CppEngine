//
// Created by Gerry on 2020-09-08.
//

#ifndef CPPMC_CHUNK_H
#define CPPMC_CHUNK_H

#include <vector>
#include <scene/Entity.h>
#include "IChunk.h"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 255
#define CHUNK_DEPTH 16
using namespace VoxEng;
#define IS_OUTSIDE (x < 0 || y < 0 ||z < 0 || x >= CHUNK_WIDTH ||y >= CHUNK_HEIGHT || z >= CHUNK_DEPTH)
class Chunk : public IChunk {
public:
    Chunk();

    Block* getBlocks() {
        return blocks;
    }

    Block getBlock(int x, int y,int z) {
        if(IS_OUTSIDE) return Block::AIR;
        return blocks[x * CHUNK_HEIGHT * CHUNK_DEPTH + y * CHUNK_DEPTH + z];
    }

    void setBlock(int x,int y,int z, Block& block) {
        if(!IS_OUTSIDE) {
            Block b = blocks[x * CHUNK_HEIGHT * CHUNK_DEPTH + y * CHUNK_DEPTH + z];
            if(y > highestY && block != Block::AIR)
                highestY = y;
            if(block != Block::AIR && b == Block::AIR) {
                opaqueBlocksPerLayer[y] ++;
            } else if(block == Block::AIR && b != Block::AIR){
                opaqueBlocksPerLayer[y] --;
            }

            if(opaqueBlocksPerLayer[y] == 0 && highestY == y) {
                for(int i = y; i >= 0; i--) {
                    if(opaqueBlocksPerLayer[i] > 0) {
                        highestY = i;
                        break;
                    }
                }
            }

            blocks[x * CHUNK_HEIGHT * CHUNK_DEPTH + y * CHUNK_DEPTH + z] = block;
        }
    }

    int opaqueBlocksPerLayer[CHUNK_HEIGHT];
    int highestY = 0;
private:
    Block blocks[CHUNK_WIDTH*CHUNK_HEIGHT*CHUNK_DEPTH];
    std::vector<Entity> entities;
};


#endif //CPPMC_CHUNK_H
