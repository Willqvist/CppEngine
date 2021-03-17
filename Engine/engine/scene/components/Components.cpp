//
// Created by Gerry on 2021-03-16.
//
#include "Components.h"
#include "Transform.h"

VoxEng::Camera::Camera() {
    projection(ProjectionMode::PERSPECTIVE);
}

void VoxEng::Camera::updateProjection() {
    projection(this->mode);
}

void VoxEng::Camera::projection(VoxEng::ProjectionMode mode) {
    this->mode = mode;
    switch (mode) {
        case ProjectionMode::ORTHOGRAPHIC: {
            glm::vec2 half = viewport * 0.5f;
            proj = glm::ortho(-half.x, half.x, -half.y, half.y);
            break;
        }
        case ProjectionMode::PERSPECTIVE: {
            proj = glm::perspective(glm::radians(fov), viewport.x/viewport.y, zNear, zFar);
            break;
        }
    }
}

void VoxEng::Camera::update(VoxEng::Transform &transform) {
    view = glm::mat4(1.0f);
    view = glm::rotate(view, glm::radians(transform.rotation().x),glm::vec3(-1.0f,0,0));
    view = glm::rotate(view, glm::radians(transform.rotation().y),glm::vec3(0,-1.0f,0));
    view = glm::rotate(view, glm::radians(transform.rotation().z),glm::vec3(0,0,-1.0f));
    view = glm::translate(view,-transform.position());
    viewProj = proj*view;
}