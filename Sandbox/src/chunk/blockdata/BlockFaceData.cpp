//
// Created by Gerry on 2021-01-16.
//

#include "BlockFaceData.h"
#include "../Block.h"
BG::FaceData BG::BlockFaceData::getData(BG::Block &block, BG::BlockFace face)  {
    return data[block].vertices->getFaceData(face);
}

BG::UVData BG::BlockFaceData::getUvData(BG::Block &block, BG::BlockFace face) {
    return data[block].uvs->getUvData(face);
}
