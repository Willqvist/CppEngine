//
// Created by Gerry on 2021-03-16.
//
#include "CameraMovement.h"
#include <core/Input.h>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/string_cast.hpp>
#include <core/KeyCode.h>
#include <scene/components/Transform.h>
void CameraMovement::update(VoxEng::Timestep ts){
    Transform& transform = this->transform();
    glm::vec2 speed = Input::getMouseDelta();
    glm::vec3 forward = glm::vec3(0,0,0);
    if(Input::isKeyDown(KeyCode::W)) {
        forward += transform.forwardXZ();
    }

    if(Input::isKeyDown(KeyCode::S)) {
        forward += -transform.forwardXZ();
    }

    if(Input::isKeyDown(KeyCode::D)) {
        forward += -transform.right();
    }

    if(Input::isKeyDown(KeyCode::A)) {
        forward += transform.right();
    }

    if(Input::isKeyDown(KeyCode::E)) {
        forward.y += 1;
    }

    if(Input::isKeyDown(KeyCode::Q)) {
        forward.y += -1;
    }
    //DEBUG_LOG("moving");
    transform.translatePosition(glm::vec3(1, 1, 1) * -forward * movementSpeed * (float)ts);
    //DEBUG_LOG("new moving, %s",to_string(transform->localPosition()).c_str());

    if(speed.x == 0 && speed.y == 0) return;
    glm::vec3 mouseDelta = glm::vec3(transform.rotation().x - speed.y * rotationSpeed, transform.rotation().y - speed.x * rotationSpeed, 0);
    glm::vec3 res = glm::lerp(transform.rotation(), mouseDelta, 0.4f * ts);
    //glm::vec3 res = glm::vec3(0,45,0);
    transform.setRotation(res);
    //DEBUG_LOG("forward: %s",to_string(transform->right()).c_str());


}