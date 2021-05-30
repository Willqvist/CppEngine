//
// Created by Gerry on 2021-05-24.
//

#include "Gizmo.h"
Ziti::GizmoInstance::GizmoInstance(const Ziti::Ref<Gizmo> &gizmo, const Ziti::Transform &transform) : _gizmo(gizmo),
                                                                                                      _transform(
                                                                                                              transform) {}
Ziti::GizmoInstance Ziti::GizmoInstance::empty = Ziti::GizmoInstance(nullptr,Ziti::Transform());

bool Ziti::GizmoInstance::valid() {
    return _gizmo != nullptr;
}

void Ziti::Gizmo::render(Ziti::Ref<Ziti::Camera> &camera, Ziti::Transform &transform) {

}
