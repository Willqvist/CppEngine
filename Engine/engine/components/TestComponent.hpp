//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_TESTCOMPONENT_HPP
#define CPPMC_TESTCOMPONENT_HPP

#include "VoxComponent.h"

namespace VoxEng {
    class TestComponent: public VoxComponent {
    public:
        void update(Timestep ts) override {

            DEBUG_LOG("wew %d",transform.x);
        };
    };
}


#endif //CPPMC_TESTCOMPONENT_HPP
