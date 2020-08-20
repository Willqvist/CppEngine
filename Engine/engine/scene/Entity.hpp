//
// Created by Gerry on 2020-08-18.
//

#ifndef CPPMC_ENTITY_HPP
#define CPPMC_ENTITY_HPP


#include <entt/entt.hpp>
#include <core/Timestep.h>
#include <core/Logger.h>
#include "Scene.h"

namespace VoxEng {
    typedef unsigned int EntityID;
    class Entity {

    public:
        Entity() {};
        Entity(entt::entity id, Scene *scene): mId(id), scene(scene){}
        template<typename T>
        T& addComponent() {
            if(hasComponent<T>())
                return getComponent<T>();
            return scene->mRegistry.emplace<T>(mId);
        };

        EntityID id() {
            return getComponent<NamedComponent>().id;
        }

        entt::entity componentIdentifier() {
            return mId;
        }

        const std::string& name() {
            return getComponent<NamedComponent>().name();
        }

        template<typename T>
        bool hasComponent() {
            return scene->mRegistry.has<T>(mId);
        };

        template<class T>
        T& getComponent() {
            return scene->mRegistry.get<T>(mId);
        };

        template<class T>
        void removeComponent() {
            return scene->mRegistry.remove_if_exists<T>(id);
        };

        Scene* getScene() {
            return scene;
        }

        ~Entity() = default;

    private:
        entt::entity mId;
        Scene* scene;
    };
}


#endif //CPPMC_ENTITY_HPP
