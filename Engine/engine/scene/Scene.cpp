//
// Created by Gerry on 2020-08-18.
//

#include "Scene.h"
#include <core/Logger.h>
#include <components/VoxComponent.h>
#include <components/ScriptComponent.hpp>
#include "scene/Entity.hpp"
#include <components/Components.h>
VoxEng::Scene::Scene() {

}

VoxEng::Entity VoxEng::Scene::createEntity() {
    Entity entity(mRegistry.create(),this);
    entity.addComponent<Transform>();
    mEntities.push_back(entity);
    return entity;
}

void VoxEng::Scene::update(Timestep ts) {
   mRegistry.view<ScriptComponent>().each([ts](ScriptComponent& comp) {
        comp.instance->update(ts);
   });
}

void VoxEng::Scene::render() {
    mRegistry.view<ScriptComponent>().each([](ScriptComponent& comp) {
        comp.instance->render();
    });
}

std::vector<VoxEng::Entity>& VoxEng::Scene::entities() {
    return mEntities;
}

void VoxEng::Scene::start() {
    mRegistry.view<ScriptComponent>().each([=](auto id, ScriptComponent& comp) {
        comp.instance = comp.createComponent();
        comp.instance->mEntity = Entity(id,this);
        comp.instance->onCreate();
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
