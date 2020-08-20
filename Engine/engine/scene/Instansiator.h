//
// Created by Gerry on 2020-08-20.
//

#ifndef CPPMC_INSTANSIATOR_H
#define CPPMC_INSTANSIATOR_H

#include <string>
#include "Entity.hpp"
#include "components/ScriptComponent.hpp"
namespace VoxEng {
    class Instansiator {
    public:
        template <typename T>
        static T* instansiateScriptableComponent(Entity& entity, const std::string& name) {
            Entity newEnt = entity.getScene()->createEntity(name);
            VoxComponent* val = newEnt.addComponent<ScriptComponent>().set<T>();
            val->mEntity = newEnt;
            val->onCreate();
            return static_cast<T*>(val);
        };

        template <typename T>
        static void addScriptComponent(Entity& entity) {
            entity.addComponent<ScriptComponent>().bind<T>();
        };
        template <typename T>
        static T* addScriptComponentImmediate(Entity& entity) {
            VoxComponent* val = entity.addComponent<ScriptComponent>().set<T>();
            val->mEntity = entity;
            val->onCreate();
            return static_cast<T*>(val);
        };
    };
}

#endif //CPPMC_INSTANSIATOR_H
