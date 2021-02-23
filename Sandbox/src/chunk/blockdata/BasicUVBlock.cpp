//
// Created by Gerry on 2021-01-18.
//

#include "BasicUVBlock.h"
#include "../Block.h"

BG::UVData BG::BasicUVBlock::getUvData(BG::BlockFace face) {
    float* uvs = nullptr;
    constexpr int diffSize = 8;
    switch(face) {
        case LEFT:uvs = uvData + diffSize*2; break;
        case RIGHT:uvs = uvData + diffSize*3; break;
        case TOP:uvs = uvData + diffSize*0; break;
        case BOTTOM:uvs = uvData + diffSize*1; break;
        case FRONT:uvs = uvData + diffSize*4; break;
        case BACK:uvs = uvData + diffSize*5; break;
    }
    return {uvs,8};
}

BG::BasicUVBlock::BasicUVBlock(int x, int y, int tw,int th, int width, int height) : width(width),height(height) {
    SideUv uv = {Sides::ALL,x,y,tw,th};
    setFaceData(uv);
}

BG::BasicUVBlock::BasicUVBlock(std::initializer_list<SideUv> uvsPerSide, int width, int height): width(width),height(height) {
    for(const SideUv& uv : uvsPerSide) {
        setFaceData(const_cast<SideUv &>(uv));
    }
}

void BG::BasicUVBlock::setFaceData(BG::SideUv &side) {
    if(side.contains(Sides::LEFT)) {
        fillData(2,side);
    }

    if(side.contains(Sides::RIGHT)) {
        fillData(3,side);
    }

    if(side.contains(Sides::TOP)) {
        fillData(0,side);
    }

    if(side.contains(Sides::BOTTOM)) {
        fillData(1,side);
    }

    if(side.contains(Sides::FRONT)) {
        fillData(4,side);
    }

    if(side.contains(Sides::BACK)) {
        fillData(5,side);
    }
}

void BG::BasicUVBlock::fillData(int index, BG::SideUv &side) {
    index *= 8;
    float x1 = side.x/(width*1.0f);
    float y1 = side.y / (height * 1.0f);

    float w = side.w/(width*1.0f);
    float h = side.h/(height*1.0f);
    uvData[index+0] = x1;
    uvData[index+1] = y1 + h;

    uvData[index+2] = x1+w;
    uvData[index+3] = y1 + h;

    uvData[index+4] = x1+w;
    uvData[index+5] = y1;

    uvData[index+6] = x1;
    uvData[index+7] = y1;
}
