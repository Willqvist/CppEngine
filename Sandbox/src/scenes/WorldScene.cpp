//
// Created by Gerry on 2020-08-23.
//

#include "WorldScene.h"
#include <scene/Entity.hpp>
#include "scene/Instansiator.h"
#include "../components/CameraMovement.h"
#include "../components/Plane.h"
#include "../layers/DebugLayer.h"

using namespace VoxEng;
void WorldScene::onSceneStart(void *data) {
    this->addLayer<DebugLayer>();

    Entity e = this->createEntity("camera");
    Entity e2 = this->createEntity("plane");

    Camera& cam = e.addComponent<Camera>();
    Ref<Window> window = application->getWindow();
    cam.viewport = glm::vec2(window->width(),window->height());
    cam.updateProjection();

    Instansiator::addScriptComponent<CameraMovement>(e);
    e.getComponent<Transform>().position.z += 10;
    Instansiator::addScriptComponent<Plane>(e2);

}
