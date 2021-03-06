//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_VOXCOMPONENT_H
#define CPPMC_VOXCOMPONENT_H

#include <core/Timestep.h>
#include <core/Core.h>
#include <scene/Entity.h>

#define Comp(name) component<name>()
#define _transform component<Transform>()
namespace VoxEng {

    class Transform;


    class VoxComponent {
    public:
        VoxComponent() {};
        virtual void onCreate() {};
        virtual void update(Timestep ts) {};
        virtual void render()  {};
        //virtual void destroy() {};
        Transform& transform();


        template<typename T>
        T& component()  {
            return mEntity.getComponent<T>();
        };


        const std::string& name();

        EntityID id() {
            return mEntity.id();
        };

        template<typename T>
        T& instansiate(const std::string& name) {
            Entity ent = mEntity.getScene()->createEntity(name);
            if(!ent.hasComponent<T>())
                return ent.addComponent<T>();
            else
                return ent.getComponent<T>();
        };

        void setEntity(Entity& entity);

        Entity getEntity();

        virtual ~VoxComponent() = default;
    protected:
        Entity mEntity;
    private:
        friend class Scene;
        friend class Entity;
    };
}
#endif