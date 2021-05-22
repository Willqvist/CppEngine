//
// Created by Gerry on 2021-05-07.
//

#ifndef CPPMC_GAMEENGINE_H
#define CPPMC_GAMEENGINE_H

#include "Memory.h"
#include <core/app/Application.h>
#include <core/rendering/RenderEngine.h>
#include <core/physics/PhysicsEngine.h>
#include <core/event/EventListener.h>
#include <core/event/Events.h>

namespace Ziti {

    class GameEngineListener;
    class GameEngine {
    public:
        GameEngine(Scope<Application>& app);
        void initialize();
        void start();
        void end();
    private:
        RenderEngine _renderEngine;
        PhysicsEngine _physicsEngine;
        Scope<Application> _app;
        bool _running = false;
        Ref<GameEngineListener> _listener;
        friend class GameEngineListener;
    };

    class GameEngineListener : public EventListener {
    public:
        GameEngineListener(GameEngine* engine) : _engine(engine) {}

        void onEvent(Event &ev) override {
            EventExecutor executor(ev);
            executor.bind<WindowCloseEvent>([&](WindowCloseEvent& close) {
                _engine->_running = false;
                return true;
            });
        }

    private:
        GameEngine* _engine;
    };
}


#endif //CPPMC_GAMEENGINE_H
