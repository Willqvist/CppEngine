//
// Created by Gerry on 2021-05-07.
//

#ifndef CPPMC_RENDERER_H
#define CPPMC_RENDERER_H

#include <vector>
#include "RenderTask.h"
#include "../../../src/core/rendering/gizmo/Gizmo.h"

namespace Ziti {
    class Renderer {
    public:
        virtual void init() = 0;
        virtual void preRender() = 0;
        virtual void render(/*const LightMap& lights, */std::vector<RenderData> tasks) = 0;
        virtual void render(Ref<Camera>& camera, std::vector<GizmoInstance> gizmos) = 0;
        virtual void postRender() = 0;
    };
}
#endif //CPPMC_RENDERER_H
