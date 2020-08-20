//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_TESTCOMPONENT_HPP
#define CPPMC_TESTCOMPONENT_HPP

#include "VoxComponent.h"
#include "ScriptComponent.hpp"
#include "../Instansiator.h"
namespace VoxEng {
    class TestComponent: public VoxComponent {
    public:

        void update(Timestep ts) override {
            this->transform->position.x += 0.2f*ts;
        };
    private:
    };
}


#endif //CPPMC_TESTCOMPONENT_HPP
