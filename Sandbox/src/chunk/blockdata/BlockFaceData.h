//
// Created by Gerry on 2021-01-16.
//

#ifndef CPPMC_BLOCKFACEDATA_H
#define CPPMC_BLOCKFACEDATA_H

#include <unordered_map>
#include <memory>
#include "BlockVerticies.h"
#include "BlockUvs.h"

namespace BG {
    class Block;
    enum BlockFace {
        LEFT, RIGHT, TOP, BOTTOM, FRONT, BACK
    };

    struct BlockModelData {
        BlockVerticies* vertices;
        BlockUvs* uvs;
    };

    struct FaceData {
        const float *vertices;
        const unsigned int *indicies;
        int vertexSize, indexSize;

        void move(int x, int y, int z, float* fill, int* index) {
            int val = *index;
            for (int i = 0; i < vertexSize; i += 3) {
                fill[val+i] = vertices[i] + x;
                fill[val+i+1] = vertices[i+1] + y;
                fill[val+i+2] = vertices[i+2] + z;
            }
            *index += vertexSize;
        }

        void indexBase(int base, unsigned int* fill, int* index) {
            int val = *index;
            for (int i = 0; i < indexSize; i ++) {
                fill[val+i] = indicies[i] + base;
            }
            *index += indexSize;
        }
    };

    class BlockFaceData {
    public:
        static FaceData getData(Block &block, BlockFace face);
        static UVData getUvData(Block &block, BlockFace face);
    private:
        static void addBlockFace(unsigned short id,BlockVerticies* vertexData) {
            data[id].vertices = vertexData;
        };

        static void addBlockUv(unsigned short id,BlockUvs* uvData) {
            if(uvData == nullptr) return;
            data[id].uvs = uvData;
        };
        static inline std::unordered_map<unsigned short, BlockModelData> data;

        friend class Block;
    };
}
#endif //CPPMC_BLOCKFACEDATA_H
