//
// Created by Gerry on 2020-09-08.
//

#ifndef CPPMC_ENTITYCREATOR_H
#define CPPMC_ENTITYCREATOR_H

#include <scene/Scene.h>
#include <scene/Entity.h>

using namespace VoxEng;
class EntityCreator {
public:
    static Entity createSheep(Ref<Scene> scene) {
        Entity e = scene->createEntity("sheep");
        //Instansiator::addScriptComponent<Sheep>(e);
        return e;
    }
};
#endif //CPPMC_ENTITYCREATOR_H
