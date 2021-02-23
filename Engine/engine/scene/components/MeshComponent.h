//
// Created by Gerry on 2021-01-14.
//

#ifndef CPPMC_MESHCOMPONENT_H
#define CPPMC_MESHCOMPONENT_H

#include "VoxComponent.h"
namespace VoxEng {
    class MeshComponent : public VoxComponent {
    public:

        void onCreate() override;

        void render() override;
    };
}


#endif //CPPMC_MESHCOMPONENT_H
