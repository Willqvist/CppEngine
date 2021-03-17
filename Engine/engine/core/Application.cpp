//
// Created by Gerry on 2020-08-10.
//

#include "Application.h"
#include "Core.h"
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tools/Tools.h>
#include <stdio.h>
#include "iostream"
#include <thread>
#include <imgui/imgui.h>
#include <scene/Scene.h>
#include <threading/MainThread.h>
#include <rendering/DebugRenderer.h>

VoxEng::Application::Application(VoxEng::WindowAttributes &attributes) {
    window = Window::createWindow(attributes);
    inputHandler = CreateRef<Input>();
    window->addEventListener(inputHandler);
    application = this;
    DebugRenderer::init();
}
void VoxEng::Application::run() {
    #ifdef DEBUG_ENABLE
        unsigned int timeSinceStart = getTime();
        int frames = 0;
        int ups = 0, prevFrame = 0, prevUpd = 0;
        float tsavg = 0;
        float maxTimePerFrame = 1 / 80.0f;
    #endif
    const float dt = 1/60.0f;
    double accumulator = 0;
    float prevFrameDelta = 0;
    while (running) {
        float time = static_cast<float>(glfwGetTime());
        Timestep timestep = time - prevFrameTime;
        prevFrameDelta = timestep;
        data.frameTime = prevFrameDelta;
        prevFrameTime = time;
        accumulator += timestep;
        while (accumulator >= dt) {
            timestep = dt;
            MainThread::callIfExists(8);
            update(timestep);
            accumulator -= dt;
#ifdef DEBUG_ENABLE
            ups++;
#endif
        }
        //if(maxTimePerFrame-timestep > 0)
        if (Input::isKeyDown(KeyCode::Escape)) {
            window->lockMouse(false);
        }
        inputHandler->poll();
        window->update();

        render();
#ifdef DEBUG_ENABLE
        renderDebug();
#endif
#ifdef DEBUG_ENABLE
        tsavg += timestep;
        frames++;
        data.frameTime = prevFrameDelta;
        if (getTime() - timeSinceStart > 1000)
        {
            if (data.frames.size() > 150)
                data.frames.erase(data.frames.begin());
            data.frames.push_back(tsavg / frames);
            timeSinceStart = getTime();
            prevFrame = frames;
            prevUpd = ups;
            data.fps = prevFrame;
            data.ups = ups;
            frames = 0;
            ups = 0;
            tsavg = 0;
        }
        //TODO: break this out to a class so Application is not dependant of IMGUI;

#endif

        window->clear();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    destroy();
}

void VoxEng::Application::onEvent(Event &ev) {
    EventExecutor exec(ev);
    exec.bind<WindowCloseEvent>(BIND_LAMBDA(onWindowCloseEvent));
    exec.bind<WindowResizeEvent>(BIND_LAMBDA(onWindowResizeEvent));
}

VoxEng::Ref<VoxEng::Window> &VoxEng::Application::getWindow() {
    return window;
}

VoxEng::Application::~Application() {

}

bool VoxEng::Application::onWindowCloseEvent(WindowCloseEvent &ev) {
    DEBUG_LOG("IM HERE CLOSING DOWN");
    running = false;
    return true;
}

bool VoxEng::Application::onWindowResizeEvent(VoxEng::WindowResizeEvent &ev) {
    return false;
}

void VoxEng::Application::update(VoxEng::Timestep &delta) {
    Ref<Scene> active = Scene::active();
    if(active)
        active->update(delta);
}

void VoxEng::Application::render() {
    Ref<Scene> active = Scene::active();
    if(active)
        active->render();
}

void VoxEng::Application::renderDebug() {
    DebugRenderer::flush();
}

VoxEng::Application *VoxEng::Application::getApplication()  {
    return application;
}

VoxEng::RuntimeData &VoxEng::Application::getRuntimeData() {
    return data;
}
