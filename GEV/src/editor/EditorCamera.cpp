//
// Created by Gerry on 2021-05-26.
//

#include <core/window/Input.h>
#include <core/window/KeyCode.h>
#include <core/window/MouseCode.h>
#include <core/utils/Time.h>
#include "editor/EditorCamera.h"
#include <core/utils/ZMath.h>
#include <core/scene/Spatial.h>
#include <glm/gtx/norm.hpp>
#define EPSILON 0.008f
ZitiView::EditorCamera::EditorCamera(Ref<RenderTarget> target) {
    _camera = CreateRef<Camera>(target);
    angles(glm::vec3(0,0,0));
    zoom(10);
    focus(glm::vec3(0,0,0));
    _distance = _distanceTarget = -5;
    _camera->background(0.1,0.1,0.1,1);
    calculateTransform();
}

void ZitiView::EditorCamera::focus(glm::vec3 position) {
    _focusTarget = position;
}

void ZitiView::EditorCamera::update() {
    bool updates = false;
    float scroll = Input::scrollSpeed();
    if(scroll != 0) {
        _distanceTarget += scroll*0.6f;
        printf("IM HERE! %f\n",scroll);
    }
    if(glm::abs(_distanceTarget - _distance) > EPSILON) {
        _distance = std::lerp(_distance,_distanceTarget,Time::delta()*7.0f);
        updates = true;
    }

    if(Input::isMouseDown(Ziti::MouseCode::ButtonMiddle)) {
        glm::vec2 md = Input::getMouseDelta();
        //printf("delta: %f :: %f\n",mp.x,mp.y);
        if(md.x != 0 || md.y != 0) {
            _anglesTarget.y += glm::radians(-md.x);
            _anglesTarget.z += glm::radians(-md.y);
        }
    }

    if(glm::distance2(_anglesTarget,_angles) > EPSILON) {
        _angles = ZMath::lerp(_angles,_anglesTarget,Time::delta()*9.0f);
        updates = true;
    }

    if(glm::distance2(_focus,_focusTarget) > EPSILON) {
        _focus = ZMath::lerp(_focus,_focusTarget,Time::delta()*9.0f);
        updates = true;
    }


    if(updates) {
        calculateTransform();
    }
}

Ref<Camera> ZitiView::EditorCamera::camera() {
    return _camera;
}


void ZitiView::EditorCamera::zoom(float distance) {
    _distance = distance;
}

float ZitiView::EditorCamera::zoom() {
    return _distance;
}

void ZitiView::EditorCamera::angles(glm::vec3 angles) {
    _angles = angles;
}

void ZitiView::EditorCamera::translateAngles(glm::vec3 angles) {
    _angles += angles;
}

glm::vec3 ZitiView::EditorCamera::calculatePosition(glm::vec3 angle, float distance) {
    return glm::vec3(
            distance*glm::sin(angle.y)*glm::cos(angle.z),
            distance*glm::sin(angle.z),
            distance*glm::cos(angle.y)*glm::cos(angle.z)
            );
}

void ZitiView::EditorCamera::calculateTransform() {
    _camera->transform().position() = calculatePosition(_angles,_distance) - _focus;
    _camera->transform().rotation() = glm::degrees(glm::vec3(-_angles.z,_angles.y,0));
    _camera->update();
}

void ZitiView::EditorCamera::nodeActive(Ref<Node> &active) {
    if(active->isClass(Ziti::Spatial::GetClass())) {
        Ref<Spatial> spatial = std::static_pointer_cast<Spatial>(active);
        focus(spatial->global().position());
        calculateTransform();
    }
}
