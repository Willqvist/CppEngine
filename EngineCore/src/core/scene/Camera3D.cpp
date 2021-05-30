//
// Created by Gerry on 2021-05-20.
//

#include "core/scene/Camera3D.h"

void Ziti::Camera3D::start() {
    Spatial::start();
    //_camera = CreateRef<Camera>(window());
}

Ziti::Ref<Ziti::Camera> Ziti::Camera3D::internal() {
    return _camera;
}

Ziti::Camera3D::Camera3D() {
    _camera = CreateRef<Camera>();
}

void Ziti::Camera3D::onPositionChange() {
    _camera->setTransform(global());
    printf("IM HERE (%f,%f,%f)!\n",_camera->transform().position().x,_camera->transform().position().y,_camera->transform().position().z);
    _camera->update();
}

void Ziti::Camera3D::update() {
    Spatial::update();
}

void Ziti::Camera3Ds(attributes);
}

::attributes(Ziti::Attributes &attributes) {
    Spatial::attribute