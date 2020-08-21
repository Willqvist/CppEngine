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

VoxEng::Application::Application(VoxEng::WindowAttributes &attributes) {
    window = Window::createWindow(attributes);
    inputHandler = CreateRef<Input>();
    window->addEventListener(inputHandler);
}

static std::vector<float> framesArr;

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
    while(running) {
        float time = static_cast<float>(glfwGetTime());
        Timestep timestep = time - prevFrameTime;
        prevFrameDelta= timestep;
        prevFrameTime = time;
        accumulator += timestep;
        while(accumulator >= dt) {
            timestep = dt;
            update(timestep);
            accumulator -= dt;
            #ifdef DEBUG_ENABLE
            ups ++;
            #endif
        }
        //if(maxTimePerFrame-timestep > 0)
        if(Input::isKeyDown(KeyCode::Escape)) {
            window->lockMouse(false);
        }
        inputHandler->poll();
        window->update();


        render();
        #ifdef DEBUG_ENABLE
                ImGui::Begin("Debug");
                renderDebug();
        #endif
        #ifdef DEBUG_ENABLE
                tsavg += timestep;
                frames++;
                if(getTime() - timeSinceStart > 1000)
                {
                    if(framesArr.size() > 150)
                        framesArr.erase(framesArr.begin());
                    framesArr.push_back(tsavg/frames);
                    timeSinceStart = getTime();
                    prevFrame = frames;
                    prevUpd = ups;
                    frames = 0;
                    ups = 0;
                    tsavg = 0;
                }
                //TODO: break this out to a class so Application is not dependant of IMGUI;
                ImGui::Text("Fps: %d",prevFrame);
                ImGui::Text("Ups: %d",prevUpd);
                ImGui::Text("Frame Time: %f",prevFrameDelta);
                glm::vec2 delta = Input::getMouseDelta();
                ImGui::Text("MouseDelta: %f | %f",delta.x,delta.y);
                ImGui::Begin("CPU");
                ImGui::PlotLines("Frame time", framesArr.data(), framesArr.size());
                ImGui::End();
                ImGui::End();

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
