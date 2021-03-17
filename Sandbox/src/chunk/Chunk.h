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
#define CLEFT 0
#define CRIGHT 1
#define CFRONT 2
#define CBACK 3
using namespace VoxEng;
#define IS_OUTSIDE_Y (y < 0 || y>= CHUNK_HEIGHT)
#define IS_OUTSIDE_Z (z < 0 || z>= CHUNK_DEPTH)
#define IS_OUTSIDE_X (x < 0 || x>= CHUNK_WIDTH)
#define IS_OUTSIDE (IS_OUTSIDE_Y || IS_OUTSIDE_X || IS_OUTSIDE_Z)
class Chunk : public IChunk {
public:
    Chunk();

    Block* getBlocks();

    Block getBlock(int x, int y,int z);
	
    bool isDirty();
    void setDirty(bool state);

	void setNeighbor(Ref<IChunk> chunk, int neigh) override;

    bool hasNeighbor(int neigh) override;
	
    void setBlock(int x,int y,int z, Block& newBlock);

    int opaqueBlocksPerLayer[CHUNK_HEIGHT];
    int highestY = 0;
private:
	int toChunkPos(int val, int size);
    Ref<IChunk> getNeighbor(int x,int z);

    Block blocks[CHUNK_WIDTH*CHUNK_HEIGHT*CHUNK_DEPTH];
    std::vector<Entity> entities;
    Ref<IChunk> neighbors[4] = {nullptr,nullptr, nullptr, nullptr};
    bool dirty = true;

};


#endif //CPPMC_CHUNK_H
