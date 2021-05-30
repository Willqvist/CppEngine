//
// Created by Gerry on 2021-05-08.
//

#ifndef CPPMC_FORWARDRENDERER_H
#define CPPMC_FORWARDRENDERER_H

#include <core/rendering/Renderer.h>

namespace Ziti {
    class ForwardRenderer : public Renderer {
    public:
        void init() override;

        void preRender() override;

        void render(std::vector<RenderData> tasks) override;

        void render(Ref<Camera>& camera,std::vector<GizmoInstance> gizmos) override;

        void postRender() override;
    };
}


#endif //CPPMC_FORWARDRENDERER_H
