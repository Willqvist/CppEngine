//
// Created by Gerry on 2020-08-23.
//

#include "DebugLayer.h"
#include <imgui/imgui.h>
#include <core/Logger.h>
#include <core/Application.h>
#include <scene/Scene.h>

void DebugLayer::onCreate() {
    Layer::onCreate();
    app = Application::getApplication();
}

void DebugLayer::render() {

    //scene data
    Ref<Scene> activeScene = Scene::active();
    Ref<Window> window = app->getWindow();
    //Camera& camera = activeScene.getComponent<Camera>();
    //Application data
    ImGui::Begin("Debug");
    RuntimeData& data = app->getRuntimeData();

    ImGui::Text("Fps: %d",data.fps);
    ImGui::Text("Ups: %d",data.ups);
    ImGui::Text("Frame Time: %f",data.frameTime);
    ImGui::PlotLines("", data.frames.data(), data.frames.size());
    ImGui::End();

    ImGui::Begin("Chunk Debug");
    ImGui::End();

    //Render settings
    ImGui::Begin("Render settings");
    if(ImGui::Button("WireFrame")) {
        DEBUG_LOG("enable wireframe");
    }

    if(ImGui::Button("Shaded")) {
        DEBUG_LOG("enable wireframe");
    }
    ImGui::End();

    //Camera settings
    ImGui::Begin("Camera settings");
    if(ImGui::Button("Lock mouse")) {
        DEBUG_LOG("enable wireframe");
        window->lockMouse(true);
    }
    ImGui::End();

}
