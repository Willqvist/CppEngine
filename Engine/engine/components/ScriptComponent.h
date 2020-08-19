//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_SCRIPTCOMPONENT_H
#define CPPMC_SCRIPTCOMPONENT_H

#include "VoxComponent.h"

namespace VoxEng {
    class ScriptComponent {
    public:
        ScriptComponent(VoxComponent* component): instance(component) {

        }

        void update(Timestep ts){
            instance->update(ts);
        }

        void render(){
            instance->render();
        }

        ~ScriptComponent() {
            delete instance;
        };

    private:
        VoxComponent* instance;

    };
}
#endif //CPPMC_SCRIPTCOMPONENT_H
