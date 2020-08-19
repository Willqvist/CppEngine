//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_VOXCOMPONENT_H
#define CPPMC_VOXCOMPONENT_H

#include <core/Timestep.h>
#include <core/Core.h>
#include <components/Components.h>
#include <scene/Entity.hpp>
#define Comp(name) component<name>()
#define transform component<Transform>()
namespace VoxEng {


    class VoxComponent {
    public:
        VoxComponent() {};
        virtual void onCreate() {};
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

        //const Entity& entity() const;

        virtual ~VoxComponent() = default;
    private:
        Entity mEntity;
        friend class Scene;
    };
}
#endif