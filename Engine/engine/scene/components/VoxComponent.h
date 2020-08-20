//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_VOXCOMPONENT_H
#define CPPMC_VOXCOMPONENT_H

#include <core/Timestep.h>
#include <core/Core.h>
#include <scene/components/Components.h>
#include <scene/Entity.hpp>

#define Comp(name) component<name>()
#define _transform component<Transform>()
namespace VoxEng {


    class VoxComponent {
    public:
        VoxComponent() {};
        virtual void onCreate() {
            this->transform = &component<Transform>();
        };
        virtual void update(Timestep ts) {};
        virtual void render()  {};
        /*
        Transform& transform() {
            return mEntity.getComponent<Transform>();
        }
         */

        template<typename T>
        T& component() {
            return mEntity.getComponent<T>();
        }

        const std::string& name() {
            return mEntity.name();
        }

        EntityID id() {
            return mEntity.id();
        }

        template<typename T>
        T& instansiate(const std::string& name) {
            Entity ent = mEntity.getScene()->createEntity(name);
            if(!ent.hasComponent<T>())
                return ent.addComponent<T>();
            else
                return ent.getComponent<T>();
        }

        void setEntity(Entity& entity) {
            this->mEntity = entity;
        }

        //const Entity& entity() const;

        virtual ~VoxComponent() = default;
    protected:
        Entity mEntity;
        Transform* transform;
    private:
        friend class Scene;
        friend class Instansiator;
    };
}
#endif