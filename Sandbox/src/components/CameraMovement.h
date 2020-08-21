//
// Created by Gerry on 2020-08-21.
//

#ifndef CPPMC_CAMERAMOVEMENT_H
#define CPPMC_CAMERAMOVEMENT_H

#include <scene/components/VoxComponent.h>
#include <core/Input.h>
#include <glm/gtx/compatibility.hpp>
using namespace VoxEng;
class CameraMovement: public VoxComponent {
public:
    void onCreate() override {
        transform = &component<Transform>();
    }

    void update(VoxEng::Timestep ts) override {
        glm::vec2 speed = Input::getMouseDelta();
        if(speed.x == 0 && speed.y == 0) return;
        float scale = 0.01f;
        glm::vec3 mouseDelta = glm::vec3(transform->rotation.x-speed.y*scale,transform->rotation.y-speed.x*scale,0);
        glm::vec3 res = glm::lerp(transform->rotation,mouseDelta,0.3f);
        transform->rotation = res;
    }
private:
    Transform* transform;
};
#endif //CPPMC_CAMERAMOVEMENT_H
