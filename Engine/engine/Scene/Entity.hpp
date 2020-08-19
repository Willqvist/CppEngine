//
// Created by Gerry on 2020-08-18.
//

#ifndef CPPMC_ENTITY_HPP
#define CPPMC_ENTITY_HPP


#include <entt/entt.hpp>
#include <core/Timestep.h>
#include <core/Logger.h>
#include <components/ScriptComponent.h>

namespace VoxEng {

    class Scene;

    class Entity {

    public:
        Entity(entt::entity id, Scene *scene): id(id), scene(scene){}
        template<typename T>
        void addComponent() {
            scene->mRegistry.emplace<T>(id);
        };

        template<typename T>
        void addScriptComponent() {
            scene->mRegistry.emplace<ScriptComponent>(id, new T());
        };

        template<typename T>
        bool hasComponent() {
            scene->mRegistry.has<T>(id);
        };

        template<class T>
        T getComponent() {
            return scene->mRegistry.get<T>(id);
        };

        template<class T>
        void removeComponent() {
            return scene->mRegistry.remove_if_exists<T>(id);
        };

        ~Entity() = default;

    private:
        entt::entity id;
        Scene* scene;
    };
}


#endif //CPPMC_ENTITY_HPP
