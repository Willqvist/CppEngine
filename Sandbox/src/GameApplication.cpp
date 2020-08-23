//
// Created by Gerry on 2020-08-10.
//

//#include <imgui/imgui.h>
#include <core/Logger.h>
#include <rendering/Texture.h>
#include <core/ResourceManager.h>
#include <rendering/VertexArray.h>
#include <rendering/VertexArrayRenderer.h>
#include <tools/Tools.h>
#include <rendering/Renderer.h>
#include <Scene/Scene.h>
#include <scene/components/TestComponent.hpp>
#include <scene/components/ScriptComponent.hpp>
#include "GameApplication.h"
#include "components/CameraMovement.h"
#include "scenes/WorldScene.h"

void GameApplication::init() {
    Scene::create<WorldScene>("world");
    Scene::goToScene("world",nullptr,0);
}

void GameApplication::destroy() {
    //scene->stop();
}

GameApplication::~GameApplication() {

}

GameApplication::GameApplication(VoxEng::WindowAttributes &attributes) : Application(attributes) {}

void GameApplication::event(VoxEng::Event &ev) {

}
