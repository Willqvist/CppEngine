//
// Created by Gerry on 2020-08-18.
//

#ifndef CPPMC_ENTITY_H
#define CPPMC_ENTITY_H


#include <entt/entt.hpp>
#include <core/Timestep.h>
#include "Scene.h"
#include "components/ScriptComponent.h"

namespace VoxEng {
    typedef unsigned int EntityID;
    class VoxComponent;
    class Entity {

    public:
        Entity();
        Entity(entt::entity id, Scene *scene);

        template<typename T>
        T& addComponent(){
            if(hasComponent<T>())
                return getComponent<T>();

            return scene->mRegistry.emplace<T>(mId);
        };

        template<class T>
        Ref<T> addDynamicComponent(){
            Ref<VoxComponent> val = addComponent<ScriptComponent>().set<T>();
            setVals(val);
            return std::dynamic_pointer_cast<T>(val);
        };


        EntityID id();

        entt::entity componentIdentifier();

        bool valid();

        const std::string& name();

        template<typename T>
        bool hasComponent() {
            return scene->mRegistry.has<T>(mId);
        }

        template<class T>
        T & getComponent() {
            return scene->mRegistry.get<T>(mId);
        }

        template<class T>
        void removeComponent() {
            return scene->mRegistry.remove_if_exists<T>(id);
        };


        Scene* getScene();

        ~Entity() = default;

    private:
        void setVals(Ref<VoxComponent>& comp);
        entt::entity mId {entt::null};
        Scene* scene = nullptr;
    };
}


#endif //CPPMC_ENTITY_H
