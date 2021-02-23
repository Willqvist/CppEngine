//
// Created by Gerry on 2021-01-14.
//
#include "Block.h"
#include "blockdata/VoxelBlock.h"
#include "blockdata/BasicUVBlock.h"

BG::VoxelBlock* BG::VoxelBlock::instance = new VoxelBlock();


BG::Block BG::Block::DIRT = Block(1,true,Sides::ALL, VoxelBlock::instance,new BasicUVBlock( {{Sides::SIDES,3*16,0,16,16},{Sides::ALL,0*16,0,16,16}},256,256));
BG::Block BG::Block::AIR = Block(0,false,Sides::NONE, VoxelBlock::instance,nullptr);
