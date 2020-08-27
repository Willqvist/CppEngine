//
// Created by Gerry on 2020-08-24.
//

#ifndef CPPMC_ROTATOR_H
#define CPPMC_ROTATOR_H
#include <scene/components/VoxComponent.h>
#include <core/Input.h>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace VoxEng;
class Rotator: public VoxComponent {
public:
    void onCreate() override {
        transform().setRotation(0,0,0);
    }

    void update(VoxEng::Timestep ts) override {
        //transform->translateRotation(0,0,12.0f*ts);
        //transform->setRotation(45,45,45);
        //transform->translateRotation(4,0,0);
        transform().translateRotation(0,1,1);
    }

    void render() override {
        DEBUG_LOG("UP: %s",to_string(transform().up()).c_str());
        //DEBUG_LOG("rendering here");
        //DEBUG_LOG("rot: %s",to_string(transform->localRotation()).c_str());
        //transform->setRotation(0,0,0);
        //DEBUG_LOG("RIGHT: %s",to_string(transform->right()).c_str());
        //DEBUG_LOG("up: %s",to_string(transform->up()).c_str());

    }
private:
    float movementSpeed = 14.2f;
    float rotationSpeed = 30.2f;

};
#endif //CPPMC_ROTATOR_H
