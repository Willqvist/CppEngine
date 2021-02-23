//
// Created by Gerry on 2020-09-08.
//

#include "Chunk.h"
#include "ChunkModelBuilder.h"
#include "ChunkBlockBuilder.h"

Chunk::Chunk() : blocks{}, opaqueBlocksPerLayer{} {
    ChunkBlockBuilder::generate(*this);
}