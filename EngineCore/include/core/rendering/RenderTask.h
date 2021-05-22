//
// Created by Gerry on 2021-05-07.
//

#ifndef CPPMC_RENDERTASK_H
#define CPPMC_RENDERTASK_H

#include <core/Memory.h>
#include <core/graphics/Material.h>
#include <core/Transform.h>

namespace Ziti {

    class Camera;
    class RenderTask {
    public:
        //virtual int tag() = 0;
        //virtual bool isInsideFrustum(const Frustum& frustum);
        virtual void process(Ref <Camera> &camera, Ref <Material> &material, Transform &transform) = 0;
    };

    struct RenderData {
        RenderTask* task;
        Ref<Camera> camera = nullptr;
        Ref<Material> material = nullptr;
        Transform transform;
    };
}


#endif //CPPMC_RENDERTASK_H
