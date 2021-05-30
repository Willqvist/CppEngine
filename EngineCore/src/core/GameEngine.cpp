//
// Created by Gerry on 2021-05-07.
//

#include "core/GameEngine.h"
#include <utility>
#include <core/utils/Time.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <core/rendering/renderers/ForwardRenderer.h>
#include <core/window/Input.h>
#define DEBUG_ENABLE

Ziti::GameEngine::GameEngine(Ziti::Scope<Ziti::Application> &app) : _app(std::move(app)) {
    Ref<Renderer> renderer = CreateRef<ForwardRenderer>();
    _renderEngine.setRenderer(renderer);
}

void Ziti::GameEngine::start() {
#ifdef DEBUG_ENABLE
    unsigned int timeSinceStart = Time::ms();
    int frames = 0;
    int ups = 0, prevFrame = 0, prevUpd = 0;
    float tsavg = 0;
    float maxTimePerFrame = 1 / 80.0f;
#endif
    _running = true;

    long double prevFrameTime = 0;
    const float dt = 1/60.0f;
    long double accumulator = 0;
    long double prevFrameDelta = 0;

    WindowAttributes attr;
    attr.height = 1080;
    attr.width = 1920;
    Ref<Window> window = Window::createWindow(attr);

    _listener = CreateRef<GameEngineListener>(new GameEngineListener(this));
    window->addEventListener(_listener);
    Ref<Input> input = CreateRef<Input>();
    window->addEventListener(input);

    _app->init(window);
    _app->start();

    timeSinceStart = Time::seconds();

    prevFrameTime = static_cast<long double>(Time::seconds());
    while (_running) {
        long double time = static_cast<long double>(Time::seconds());
        long double timestep = time - prevFrameTime;
        prevFrameDelta = timestep;
        prevFrameTime = time;
        accumulator += timestep;
        while (accumulator >= dt) {
            timestep = dt;
            Time::_delta = timestep;
            _app->update();
            accumulator -= dt;

            #ifdef DEBUG_ENABLE
                ups++;
            #endif
        }
        /*
        //if(maxTimePerFrame-timestep > 0)
        if (Input::isKeyDown(KeyCode::Escape)) {
            window->lockMouse(false);
        }
        inputHandler->poll();
        window->update();

        render();
        renderDebug();
         */
        input->poll();
        window->update();
        _app->render(_renderEngine);
        _renderEngine.flush();
        _app->postRender();
        window->swap();
#ifdef DEBUG_ENABLE
        //renderDebug();
#endif
#ifdef DEBUG_ENABLE
        tsavg += timestep;
        frames++;
        if (Time::seconds() - timeSinceStart > 1000)
        {
            timeSinceStart = Time::seconds();
            prevFrame = frames;
            prevUpd = ups;
            frames = 0;
            ups = 0;
            tsavg = 0;
        }
        //TODO: break this out to a class so Application is not dependant of IMGUI;

#endif

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    end();
}

void Ziti::GameEngine::initialize() {
    start();
}

void Ziti::GameEngine::end() {
    _app->stop();
}
