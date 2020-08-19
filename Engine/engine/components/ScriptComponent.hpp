//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_SCRIPTCOMPONENT_HPP
#define CPPMC_SCRIPTCOMPONENT_HPP

#include "components/VoxComponent.h"
namespace VoxEng {

    class ScriptComponent {
    public:

        ScriptComponent() = default;

        template<typename T>
        void bind() {
            this->createComponent = []() {return new T();};
            this->destroyComponent = [](ScriptComponent* comp){delete comp->instance; comp->instance = nullptr;};

        };

        ~ScriptComponent() {
            destroyComponent(this);
        };

    protected:
        std::function<VoxComponent*()> createComponent;
        std::function<void(ScriptComponent*)> destroyComponent;
        VoxComponent* instance = nullptr;
        friend class Scene;
    };
}
#endif //CPPMC_SCRIPTCOMPONENT_HPP
