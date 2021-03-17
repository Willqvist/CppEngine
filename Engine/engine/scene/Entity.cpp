//
// Created by Gerry on 2021-01-15.
//

#include "Entity.h"
#include "components/VoxComponent.h"
#include "components/ScriptComponent.h"
#include "scene/Scene.h"
#include <core/Logger.h>
#include <scene/components/NamedComponent.h>

VoxEng::Entity::Entity() {

}

VoxEng::Entity::Entity(entt::entity id, VoxEng::Scene *scene): mId(id), scene(scene){}

bool VoxEng::Entity::valid()  {
    if(scene == nullptr) return false;
    return scene->mRegistry.valid(mId);
}

void VoxEng::Entity::setVals(Ref<VoxComponent>& comp) {
    comp->mEntity = *this;
    comp->onCreate();
}

VoxEng::EntityID VoxEng::Entity::id() {
    return getComponent<NamedComponent>().id;
}

entt::entity VoxEng::Entity::componentIdentifier() {
    return mId;
}

const std::string &VoxEng::Entity::name() {
    return getComponent<NamedComponent>().name();
}

VoxEng::Scene *VoxEng::Entity::getScene() {
    return scene;
};

