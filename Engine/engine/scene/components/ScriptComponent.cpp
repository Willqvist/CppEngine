//
// Created by Gerry on 2021-01-15.
//

#include <core/Timestep.h>
#include "ScriptComponent.h"
#include "VoxComponent.h"
#include <typeinfo>
void VoxEng::ScriptComponent::update(Timestep ts) {
    for(Ref<VoxComponent> comp : components) {
        comp->update(ts);
    }
}

void VoxEng::ScriptComponent::render() {
    for(Ref<VoxComponent> comp : components) {
        comp->render();
    }
}


VoxEng::ScriptComponent::~ScriptComponent() {
    components.clear();
}