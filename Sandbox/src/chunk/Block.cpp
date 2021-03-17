//
// Created by Gerry on 2021-01-14.
//
#include "Block.h"
#include "blockdata/VoxelBlock.h"
#include "blockdata/BasicUVBlock.h"

BG::VoxelBlock* BG::VoxelBlock::instance = new VoxelBlock();


BG::Block BG::Block::DIRT = Block(1,true,Sides::ALL, VoxelBlock::instance,new BasicUVBlock( {{Sides::SIDES,3*16,0,16,16},{Sides::ALL,0*16,0,16,16}},256,256));
BG::Block BG::Block::AIR = Block(0,false,Sides::NONE, VoxelBlock::instance,nullptr);

BG::Block::Block(unsigned short id, bool isSolid, BG::Sides opaqueSides, BG::BlockVerticies *vertexData,
                 BG::BlockUvs *uvs) : id(id) {
    data[id] = {isSolid, opaqueSides};
    BlockFaceData::addBlockFace(id, vertexData);
    BlockFaceData::addBlockUv(id, uvs);
}

bool BG::Block::isOpaque(BG::Sides sides) {
    return ((int32_t)data[id].opaqueSides & (int32_t)sides) > 0;
}

bool BG::Block::isFullyTransparent() {
    return data[id].opaqueSides == Sides::NONE;
}

bool BG::Block::operator==(BG::Block &b) {
    return b.id == this->id;
}

BG::Block::operator unsigned short() {
    return id;
}
