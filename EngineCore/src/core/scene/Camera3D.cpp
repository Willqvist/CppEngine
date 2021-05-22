//
// Created by Gerry on 2021-05-20.
//

#include "core/scene/Camera3D.h"

void Ziti::Camera3D::start() {
    //_camera = CreateRef<Camera>(window());
}

Ziti::Ref<Ziti::Camera> Ziti::Camera3D::internal() {
    return _camera;
}

Ziti::Camera3D::Camera3D() {
    _camera = CreateRef<Camera>();
}

