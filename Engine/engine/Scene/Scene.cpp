//
// Created by Gerry on 2020-08-18.
//

#include "Scene.h"
#include <core/Logger.h>
#include <components/ScriptComponent.h>

VoxEng::Scene::Scene() {

}

VoxEng::Ref<VoxEng::Entity> VoxEng::Scene::createEntity() {
    Ref<Entity> entity = CreateRef<Entity>(mRegistry.create(),this);
    mEntities.push_back(entity);
    return entity;
}

void VoxEng::Scene::update(Timestep ts) {
   mRegistry.view<ScriptComponent>().each([ts](auto& comp) {
        comp.update(ts);
   });
}

void VoxEng::Scene::render() {
    mRegistry.view<ScriptComponent>().each([](auto& comp) {
        comp.render();
    });
}

std::vector<VoxEng::Ref<VoxEng::Entity>>& VoxEng::Scene::entities() {
    return mEntities;
}

VoxEng::Scene::~Scene() {

}
