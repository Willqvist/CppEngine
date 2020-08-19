//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_VOXCOMPONENT_H
#define CPPMC_VOXCOMPONENT_H

#include <core/Timestep.h>

namespace VoxEng {
    class VoxComponent {
    public:
        VoxComponent() = default;
        virtual void update(Timestep ts) {};
        virtual void render()  {};
        ~VoxComponent() = default;
    };
}


#endif //CPPMC_VOXCOMPONENT_H
