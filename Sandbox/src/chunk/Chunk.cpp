//
// Created by Gerry on 2020-09-08.
//

#include "Chunk.h"
#include "ChunkModelBuilder.h"
#include "ChunkBlockBuilder.h"

Chunk::Chunk() : blocks{}, opaqueBlocksPerLayer{} {

}

Block *Chunk::getBlocks() {
    return blocks;
}

Block Chunk::getBlock(int x, int y, int z) {
    if (IS_OUTSIDE_Y)
        return Block::AIR;
    if (IS_OUTSIDE_Z || IS_OUTSIDE_X) {
        Ref<IChunk> neigh = getNeighbor(x,z);
        if(neigh != nullptr)
        {
            return neigh->getBlock(
                    toChunkPos(x,CHUNK_WIDTH),
                    y,
                    toChunkPos(z, CHUNK_DEPTH)
            );
        }
        return Block::AIR;
    }
    return blocks[x * CHUNK_HEIGHT * CHUNK_DEPTH + y * CHUNK_DEPTH + z];
}

bool Chunk::isDirty() {
    return dirty;
}

void Chunk::setDirty(bool state) {
    this->dirty = state;
}

void Chunk::setNeighbor(Ref<IChunk> chunk, int neigh) {
    if(this->neighbors[neigh] != nullptr)
    {

    }
    this->neighbors[neigh] = chunk;
}

bool Chunk::hasNeighbor(int neigh) {
    return neighbors[neigh] != nullptr;
}

void Chunk::setBlock(int x, int y, int z, Block &newBlock) {
    if(!IS_OUTSIDE) {
        Block prevBlock = blocks[x * CHUNK_HEIGHT * CHUNK_DEPTH + y * CHUNK_DEPTH + z];
        if(y > highestY && newBlock != Block::AIR)
            highestY = y;
        if(newBlock != Block::AIR && prevBlock == Block::AIR) {
            opaqueBlocksPerLayer[y] ++;
        } else if(newBlock == Block::AIR && prevBlock != Block::AIR){
            opaqueBlocksPerLayer[y] --;
        }

        if(opaqueBlocksPerLayer[y] <= 0 && highestY == y) {
            for(int i = y; i >= 0; i--) {
                if(opaqueBlocksPerLayer[i] > 0) {
                    highestY = i;
                    break;
                }
            }
        }
        dirty = false;
        blocks[x * CHUNK_HEIGHT * CHUNK_DEPTH + y * CHUNK_DEPTH + z] = newBlock;
    }
}

int Chunk::toChunkPos(int val, int size) {
    return val < 0 ? size + val : ((val >= size) ? val - size : val);
}

Ref<IChunk> Chunk::getNeighbor(int x, int z) {
    if (x < 0) return neighbors[CLEFT];
    if (z < 0) return neighbors[CBACK];
    if (x >= CHUNK_WIDTH) return neighbors[CRIGHT];
    if (z >= CHUNK_DEPTH) return neighbors[CFRONT];
    return nullptr;
}