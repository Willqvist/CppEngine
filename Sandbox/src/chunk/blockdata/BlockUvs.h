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
        void fill(std::vector<float>& out) {
            for(int i = 0 ; i < size; i+= 2) {
                out.push_back(data[i]);
                out.push_back(data[i+1]);
            }
        }

    };

    class BlockUvs {
    public:
        virtual UVData getUvData(BlockFace face) = 0;
    };
}
#endif //CPPMC_BLOCKUVS_H
