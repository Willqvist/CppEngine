//
// Created by Gerry on 2020-08-10.
//
#include "GameApplication.h"
#include <Scene/Scene.h>
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
