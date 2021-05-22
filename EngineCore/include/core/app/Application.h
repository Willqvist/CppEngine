//
// Created by Gerry on 2021-05-07.
//

#ifndef CPPMC_APPLICATION_H
#define CPPMC_APPLICATION_H

#include <core/rendering/RenderEngine.h>
#include <core/Memory.h>
#include <core/window/Window.h>
#include <core/scene/SceneTree.h>

namespace Ziti {
    class Application {
    public:

        const void init(Ref<Window> window) {
            if(_initiated) return;
            _window = window;
            _scene = CreateRef<SceneTree>();
            _initiated = true;
        }

        virtual void start() = 0;
        virtual void update() = 0;
        virtual void render(RenderEngine& engine) = 0;
        virtual void postRender() {};
        virtual void stop() = 0;
        Ref<Window> window() {
            return _window;
        }


        Ref<SceneTree> getNodeTree() {
            return _scene;
        }

    private:
        Ref<Window> _window;
        Ref<SceneTree> _scene;
        bool _initiated = false;
    };
}

#endif //CPPMC_APPLICATION_H
