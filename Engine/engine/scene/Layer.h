//
// Created by Gerry on 2020-08-23.
//

#ifndef CPPMC_LAYER_H
#define CPPMC_LAYER_H

#include <core/Timestep.h>

namespace VoxEng {
    class Layer {
    public:
        virtual void onCreate() {};
        virtual void update(Timestep ts) {};
        virtual void render() {};
    };
}


#endif //CPPMC_LAYER_H
