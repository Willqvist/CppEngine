//
// Created by Gerry on 2021-05-07.
//

#ifndef CPPMC_RENDERENGINE_H
#define CPPMC_RENDERENGINE_H

#include <core/Memory.h>
#include "Renderer.h"
#include "Viewport.h"
#include "RenderTask.h"
#include "RenderTarget.h"
#include "Camera.h"
#include <vector>
#include <unordered_set>
namespace Ziti {



    class RenderEngine {
    public:
        void setRenderer(Ref<Renderer> renderer);
        void setCamera(Ref<Camera> camera);
        void addRenderTask(RenderData& data);

    private:
        void flush();
        std::vector<RenderData> _tasks;
        std::unordered_set<Ref<Camera>> _cameras;
        Ref<Camera> _camera;
        Ref<Renderer> _renderer;
        friend class GameEngine;
    };
}


#endif //CPPMC_RENDERENGINE_H
