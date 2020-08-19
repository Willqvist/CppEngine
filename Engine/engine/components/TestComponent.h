//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_TESTCOMPONENT_H
#define CPPMC_TESTCOMPONENT_H

#include "VoxComponent.h"

namespace VoxEng {
    class TestComponent: public VoxComponent {
    public:

        TestComponent() = default;
        ~TestComponent() = default;

        void update(Timestep ts) override;

        void render() override;

    };
}


#endif //CPPMC_TESTCOMPONENT_H
