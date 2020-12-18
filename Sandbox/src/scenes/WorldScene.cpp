//
// Created by Gerry on 2020-08-23.
//

#include "WorldScene.h"
#include <scene/Entity.hpp>
#include "scene/Instansiator.h"
#include "../components/CameraMovement.h"
#include "../components/Plane.h"
#include "../layers/DebugLayer.h"
#include "../components/Rotator.h"

using namespace VoxEng;
void WorldScene::onSceneStart(void *data) {
    this->addLayer<DebugLayer>();
    Entity e2 = this->createEntity("plane");
    Entity e3 = this->createEntity("plane2",e2);
    Entity e = this->createEntity("camera");
    Camera& cam = e.addComponent<Camera>();
    Ref<Window> window = application->getWindow();
    cam.viewport = glm::vec2(window->width(),window->height());
    cam.updateProjection();

    e3.getComponent<Transform>().translateY(TransformType::POSITION,2);
    e3.getComponent<Transform>().setScale(0.2f,0.2f,0.2f);

    Instansiator::addScriptComponent<CameraMovement>(e);
    e.getComponent<Transform>().translateZ(TransformType::POSITION,10);
    Instansiator::addScriptComponent<Plane>(e2);
    Instansiator::addScriptComponent<Rotator>(e2);
    Plane* p = Instansiator::addScriptComponent<Plane>(e3);
    //UpVectorDisplay* up  = Instansiator::addScriptComponent<UpVectorDisplay>(e3);
    //up->setOrigin(e2);
    p->material->set("m_Color",glm::vec3(1,0,0));

    //Instansiator::addScriptComponent<Plane>(e4);
    //VecorDot* d = Instansiator::addScriptComponentImmediate<VecorDot>(e4);
    //d->target = &e2.transform();
}
