//
// Created by Gerry on 2021-01-15.
//

#include "Entity.h"
#include "components/VoxComponent.h"

bool VoxEng::Entity::valid()  {
    if(scene == nullptr) return false;
    return scene->mRegistry.valid(mId);
}

void VoxEng::Entity::setVals(Ref<VoxComponent>& comp) {
    comp->mEntity = *this;
    comp->onCreate();
}



