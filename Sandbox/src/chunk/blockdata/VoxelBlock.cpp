//
// Created by Gerry on 2021-01-16.
//

#include <cstdio>
#include "VoxelBlock.h"
#include "BlockFaceData.h"

BG::FaceData BG::VoxelBlock::getFaceData(BlockFace face) {
    const float* verticies = nullptr;
    constexpr int diffSize = 3*4;
    switch(face) {
        case LEFT:verticies = faceData + diffSize*2; break;
        case RIGHT:verticies = faceData + diffSize*3; break;
        case TOP:verticies = faceData + diffSize*5; break;
        case BOTTOM:verticies = faceData + diffSize*4; break;
        case FRONT:verticies = faceData; break;
        case BACK:verticies = faceData + diffSize*1; break;
    }
    return {verticies,indiciesPerFace, diffSize,6};
}
