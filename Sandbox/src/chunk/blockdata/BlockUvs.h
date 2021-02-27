//
// Created by Gerry on 2021-01-18.
//

#ifndef CPPMC_BLOCKUVS_H
#define CPPMC_BLOCKUVS_H

#include <vector>

namespace BG {
    enum BlockFace;

    struct UVData {
        float* data;
        int size;
        void fill(float* fill, int* index) {
            int val = *index;
            for (int i = 0; i < size; i += 2) {
                fill[val+i] = data[i];
                fill[val+i+1] = data[i+1];
            }
            *index += size;
        }

    };

    class BlockUvs {
    public:
        virtual UVData getUvData(BlockFace face) = 0;
    };
}
#endif //CPPMC_BLOCKUVS_H
