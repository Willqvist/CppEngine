//
// Created by Gerry on 2020-08-23.
//

#include "WorldScene.h"
#include <scene/Entity.h>
#include <scene/components/Components.h>
#include <core/Window.h>
#include <scene/components/Transform.h>
#include <core/Application.h>
#include "../components/CameraMovement.h"
#include "../layers/DebugLayer.h"
#include "../components/ChunkComponent.h"
#include "../components/WorldManager.h"

using namespace VoxEng;
void WorldScene::onSceneStart(void *data) {

    //SceneThread managerThread = this->createThread();
    this->addLayer<DebugLayer>();
    Entity e2 = this->createEntity("plane");
    Entity e3 = this->createEntity("plane2",e2);
    Entity e = this->createEntity("camera");
    Entity managerEnt = this->createEntity("ChunkManager");

    Ref<WorldManager> manager = managerEnt.addDynamicComponent<WorldManager>();

    Camera& cam = e.addComponent<Camera>();
    e.addDynamicComponent<CameraMovement>();
    e.getComponent<Transform>().setPosition({ 0,150,0 });
    manager->follow(e);
    Ref<Window> window = application->getWindow();
    cam.viewport = glm::vec2(window->width(),window->height());
    cam.updateProjection();


    e3.getComponent<Transform>().translatePosition({0,0,2});
    e3.getComponent<Transform>().setScale(0.2f,0.2f,0.2f);

    e.addDynamicComponent<CameraMovement>();

    //e.getComponent<Transform>().translateZ(TransformType::POSITION,10);
    //Ref<ChunkComponent> comp = cunk.addDynamicComponent<ChunkComponent>();

    //e2.addDynamicComponent<Rotator>();

    //Plane* p = e3.addDynamicComponent<Plane>();
    //p->material->set("m_Color",glm::vec3(1,0,0));


    //thr.start(nullptr);
}
