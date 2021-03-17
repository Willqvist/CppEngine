//
// Created by Gerry on 2021-03-16.
//
#include "NamedComponent.h"

VoxEng::NamedComponent::NamedComponent() {
    id = globalId ++;
}

void VoxEng::NamedComponent::name(const std::string &name) {
    this->mName = name;
}

std::string &VoxEng::NamedComponent::name() {
    return mName;
}

int VoxEng::NamedComponent::globalId = 0;