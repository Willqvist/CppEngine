//
// Created by Gerry on 2021-05-07.
//

#ifndef CPPMC_RENDERABLE_H
#define CPPMC_RENDERABLE_H

#include <core/Transform.h>
#include "RenderTask.h"

namespace Ziti {
    class Renderable : public RenderTask {
    public:
        void process(Ref <Camera> &camera, Ref <Material> &material, Transform &transform) override;
    };
}

#endif //CPPMC_RENDERABLE_H
