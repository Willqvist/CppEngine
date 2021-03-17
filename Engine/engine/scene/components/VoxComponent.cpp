//
// Created by Gerry on 2020-08-19.
//

#include "VoxComponent.h"
#include <scene/components/Transform.h>

VoxEng::Transform &VoxEng::VoxComponent::transform() {
    return mEntity.getComponent<Transform>();
}

const std::string &VoxEng::VoxComponent::name() {
    return mEntity.name();
}

void VoxEng::VoxComponent::setEntity(VoxEng::Entity &entity) {
    this->mEntity = entity;
}

VoxEng::Entity VoxEng::VoxComponent::getEntity() {
    return mEntity;
}