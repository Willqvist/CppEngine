//
// Created by Gerry on 2020-08-18.
//

#include "Scene.h"
#include <core/Logger.h>
#include "components/VoxComponent.h"
#include "components/ScriptComponent.hpp"
#include "scene/Entity.hpp"
#include "components/Components.h"
#include <rendering/Renderer.h>
VoxEng::Scene::Scene() {

}

VoxEng::Entity VoxEng::Scene::createEntity(const std::string& name, Entity& parent) {
    Entity entity(mRegistry.create(),this);
    Transform& trans = entity.addComponent<Transform>();
    entity.addComponent<ScriptComponent>();
    trans.parent = &parent.getComponent<Transform>();
    NamedComponent& comp = entity.addComponent<NamedComponent>();
    comp.name(name);
    mEntities.push_back(entity);
    return entity;
}

VoxEng::Entity VoxEng::Scene::createEntity(const std::string &name) {
    Entity entity(mRegistry.create(),this);
    entity.addComponent<Transform>();
    NamedComponent& comp = entity.addComponent<NamedComponent>();
    entity.addComponent<NamedComponent>();

    comp.name(name);
    mEntities.push_back(entity);
    return entity;
}

void VoxEng::Scene::update(Timestep ts) {
   mRegistry.view<ScriptComponent>().each([ts](ScriptComponent& comp) {
        comp.update(ts);
   });
}

void VoxEng::Scene::render() {
    Camera* mainCamera = nullptr;
    Transform* cameraTransform = nullptr;
    auto view = mRegistry.view<Transform, Camera>();

    for(auto entity: view) {
        auto [transformComp, camera] = view.get<Transform, Camera>(entity);
        if(camera.main) {
            mainCamera = &camera;
            cameraTransform = &transformComp;
            break;
        }
    }
    mainCamera->update(*cameraTransform);
    Renderer::begin(mainCamera);
    mRegistry.view<ScriptComponent>().each([](ScriptComponent& comp) {
        comp.render();
    });
    //Renderer::end();
}

std::vector<VoxEng::Entity>& VoxEng::Scene::entities() {
    return mEntities;
}

void VoxEng::Scene::start() {
    mRegistry.view<ScriptComponent>().each([=](auto id, ScriptComponent& comp) {
        comp.build([&](VoxComponent* component) {
            component->mEntity = Entity(id,this);
            component->onCreate();
        });
    });
}

void VoxEng::Scene::stop() {
    mRegistry.each([=](auto entity) {
        mRegistry.destroy(entity);
        //comp.instance->onCreate();
    });
}

VoxEng::Scene::~Scene() {

}
