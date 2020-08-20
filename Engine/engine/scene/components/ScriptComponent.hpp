//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_SCRIPTCOMPONENT_HPP
#define CPPMC_SCRIPTCOMPONENT_HPP
#include <iostream>
#include "VoxComponent.h"
namespace VoxEng {

    class ScriptComponent {
    public:
        typedef std::pair<std::function<VoxComponent*()>,std::function<void(ScriptComponent*,int)>> ComponentMethods;
        ScriptComponent() = default;

        template<typename T>
        void bind() {
            boundedMethods.emplace_back(
                    []()->VoxComponent* {return static_cast<VoxComponent*>(new T());},
                    [&](ScriptComponent* comp, int index){delete components[index]; components[index] = nullptr;}
                    );
        };

        template<typename F>
        void build(F& callback) {
            for(ComponentMethods& methods : boundedMethods) {
                VoxComponent* comp = methods.first();
                callback(comp);
                components.push_back(comp);
            }
        }

        void update(Timestep ts) {
            //DEBUG_LOG("SIZE: %d\n", components.size());
            for(VoxComponent* comp : components) {
                comp->update(ts);
            }
        }

        void render() {
            for(VoxComponent* comp : components) {
                comp->render();
            }
        }

        ~ScriptComponent() {
            //destroyComponent(this);
        };

    protected:

        template<typename T>
        T* set() {
            T* instance = new T();
            components.push_back(static_cast<VoxComponent*>(instance));
            return instance;
            //return static_cast<T&>(*instance);
        };

        std::vector<ComponentMethods> boundedMethods;
        std::vector<VoxComponent*> components;
        friend class Scene;
        friend class Instansiator;
    };
}
#endif //CPPMC_SCRIPTCOMPONENT_HPP
