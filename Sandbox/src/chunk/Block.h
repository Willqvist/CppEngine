//
// Created by Gerry on 2021-01-14.
//

#ifndef CPPMC_BLOCK_H
#define CPPMC_BLOCK_H

#include <unordered_map>
#include "blockdata/BlockFaceData.h"
#include "blockdata/BlockUvs.h"

namespace BG {

    enum class Sides: uint32_t {
        NONE = 0,
        LEFT = 1,
        RIGHT=2,
        TOP=4,
        BOTTOM=8,
        FRONT=16,
        BACK=32,
        ABOVE = TOP | BOTTOM,
        SIDES = LEFT | RIGHT | FRONT | BACK,
        ALL = LEFT | RIGHT | TOP | BOTTOM | FRONT | BACK
    };

    struct BlockData {
        bool isSolid = true;
        Sides opaqueSides = Sides::NONE;
    };

    class Block {
    public:
        static Block DIRT;
        static Block AIR;

        Block() : id(0) {}

        bool isOpaque(Sides sides) {
            return ((int32_t)data[id].opaqueSides & (int32_t)sides) > 0;
        }

        bool isFullyTransparent() {
            return data[id].opaqueSides == Sides::NONE;
        }

        bool operator ==(Block& b) {
            return b.id == this->id;
        }

        operator unsigned short() {
            return id;
        }

        Block(unsigned short id, bool isSolid, Sides opaqueSides,BlockVerticies* vertexData, BlockUvs* uvs) : id(id) {
            data[id] = {isSolid, opaqueSides};
            BlockFaceData::addBlockFace(id, vertexData);
            BlockFaceData::addBlockUv(id, uvs);
        }


    private:
        unsigned short id;
        static inline std::unordered_map<unsigned short, BlockData> data;
    };

}
#endif //CPPMC_BLOCK_H
