//
// Created by Gerry on 2021-05-08.
//

#include "core/rendering/Camera.h"
#include <glm/ext.hpp>
#include <core/graphics/GraphicsCommand.h>

void Ziti::Camera::update() {
    _view = glm::mat4(1.0f);
    _view = glm::rotate(_view, glm::radians(_transform.rotation().x),glm::vec3(-1.0f,0,0));
    _view = glm::rotate(_view, glm::radians(_transform.rotation().y),glm::vec3(0,-1.0f,0));
    _view = glm::rotate(_view, glm::radians(_transform.rotation().z),glm::vec3(0,0,-1.0f));
    _view = glm::translate(_view,_transform.position());
    //printf("rot: %f - %f - %f \n",_transform.position().x,_transform.position().y,_transform.position().z);
    _viewProj = _projection*_view;
}

glm::mat4 Ziti::Camera::getVP() {
    return _viewProj;
}

glm::mat4 Ziti::Camera::getView() {
    return _view;
}

glm::mat4 Ziti::Camera::getProjection() {
    return _projection;
}

void Ziti::Camera::setProjection(Ziti::ProjectionType type) {
    _type = type;
    updateProjection();
}

void Ziti::Camera::updateProjection() {
    Viewport& viewport = _target->viewport();
    printf("viewport size: %d :: %d\n",viewport.width(),viewport.height());
    switch (_type) {
        case ProjectionType::ORTHOGRAPHIC: {
            float hWidth = viewport.width()/2.0f;
            float hHeight = viewport.height()/2.0f;
            _projection = glm::ortho(-hWidth,hWidth,-hHeight,hHeight);
            break;
        }
        case ProjectionType::PERSPECTIVE: {
            _projection = glm::perspective(glm::radians(70.0f), (float)(viewport.width()/(viewport.height()*1.0f)), 0.01f, 1000.0f);
            break;
        }
    }
    update();
}

Ziti::Camera::Camera() {

}

void Ziti::Camera::clear() {
    GraphicsCommand::clearScreenColor(_background.r,_background.g,_background.b,_background.a); //TODO: change to background color variable;
    GraphicsCommand::clear(BUFFER_BIT::COLOR | BUFFER_BIT::DEPTH);
    _target->clear();
}

void Ziti::Camera::background(float r, float g, float b, float a) {
    _background = glm::vec4(r,g,b,a);
}
