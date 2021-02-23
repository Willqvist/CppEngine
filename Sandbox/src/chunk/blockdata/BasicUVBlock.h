//
// Created by Gerry on 2021-01-18.
//

#ifndef CPPMC_BASICUVBLOCK_H
#define CPPMC_BASICUVBLOCK_H

#include "BlockUvs.h"
namespace BG {
    enum class Sides: uint32_t;

    struct SideUv {
        Sides sides;
        int x, y, w, h;
        bool contains(Sides side) {
            return ((uint32_t)sides & (uint32_t)side) > 0;
        }
    };

    class BasicUVBlock : public BlockUvs {
    public:
        BasicUVBlock(int x, int y, int tw,int th, int width, int height);
        BasicUVBlock(std::initializer_list<SideUv> uvsPerSide, int width, int height);
        UVData getUvData(BlockFace face) override;
        static BasicUVBlock* instance;
    private:
        void setFaceData(SideUv& side);
        void fillData(int index, SideUv& side);
        int width,height;
        float uvData[8*6] = {
                //top
                0,1,
                1,1,
                1,0,
                0,0,

                //bottom
                0,1,
                1,1,
                1,0,
                0,0,

                //left
                0,1,
                1,1,
                1,0,
                0,0,

                //right
                0,1,
                1,1,
                1,0,
                0,0,

                //front
                0,1,
                1,1,
                1,0,
                0,0,

                //back
                0,1,
                1,1,
                1,0,
                0,0
        };
    };
}


#endif //CPPMC_BASICUVBLOCK_H
