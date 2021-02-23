//
// Created by Gerry on 2020-09-08.
//

#ifndef CPPMC_CHUNKBLOCKBUILDER_H
#define CPPMC_CHUNKBLOCKBUILDER_H


#include "Chunk.h"

class ChunkBlockBuilder {
public:
    static void generate(Chunk& chunk) {
        std::srand(23224);
        for(int x = 0; x < CHUNK_WIDTH; x++) {
            for(int z = 0; z < CHUNK_DEPTH; z++) {
                for(int y = 0; y < CHUNK_HEIGHT; y++) {
                    if(std::rand() % 100 > 90 && y < 120)
                        chunk.setBlock(x,y,z,Block::DIRT);
                    else
                        chunk.setBlock(x,y,z,Block::AIR);
                }
            }
        }
    }
};


#endif //CPPMC_CHUNKBLOCKBUILDER_H
