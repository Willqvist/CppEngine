//
// Created by Gerry on 2021-01-16.
//

#ifndef CPPMC_VOXELBLOCK_H
#define CPPMC_VOXELBLOCK_H

#include "BlockVerticies.h"

namespace BG {
    class VoxelBlock : public BlockVerticies {
    public:

        FaceData getFaceData(BlockFace face) override;
        static VoxelBlock* instance;
    private:

        static inline const unsigned int indiciesPerFace[6] = {
                0,1,2,
                2,3,0,
        };

        static inline const float faceData[3*4*6] = {
                //front
                0,0,0,
                1,0,0,
                1,1,0,
                0,1,0,

                //back
                0,0,1,
                1,0,1,
                1,1,1,
                0,1,1,

                //left
                0,0,0,
                0,0,1,
                0,1,1,
                0,1,0,

                //right
                1,0,0,
                1,0,1,
                1,1,1,
                1,1,0,

                //bottom
                0,0,0,
                1,0,0,
                1,0,1,
                0,0,1,

                //top
                0,1,0,
                1,1,0,
                1,1,1,
                0,1,1
        };
    };
}

#endif //CPPMC_VOXELBLOCK_H
