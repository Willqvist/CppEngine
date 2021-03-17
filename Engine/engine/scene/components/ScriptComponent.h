//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_SCRIPTCOMPONENT_H
#define CPPMC_SCRIPTCOMPONENT_H
#include <iostream>
#include <functional>
#include "core/Core.h"
namespace VoxEng {
    class VoxComponent;
    class Entity;
    class ScriptComponent {
    public:
        typedef std::pair<std::function<VoxComponent*()>,std::function<void(ScriptComponent*,int)>> ComponentMethods;
        ScriptComponent() = default;

        void update(Timestep ts);

        void render();

        ~ScriptComponent();

    protected:

        template<typename T>
        Ref<VoxComponent> set(){
            T* t = new T();
            Ref<T> instance = CreateRef<T>(t);
            Ref<VoxComponent> v = std::dynamic_pointer_cast<VoxComponent>(instance);
            components.push_back(v);
            return v;
        }

        std::vector<ComponentMethods> boundedMethods;
        std::vector<Ref<VoxComponent>> components;
        friend class Scene;
        friend class Entity;
    };
}
#endif //CPPMC_SCRIPTCOMPONENT_H
