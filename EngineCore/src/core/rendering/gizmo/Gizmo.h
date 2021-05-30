//
// Created by Gerry on 2021-05-24.
//

#ifndef CPPMC_GIZMO_H
#define CPPMC_GIZMO_H

#include <core/Memory.h>
#include <core/Transform.h>
#include <core/rendering/Camera.h>

namespace Ziti {
    class Gizmo;
    class RenderEngine;
    class GizmoInstance {
    public:
        Ref<Gizmo> _gizmo;
        Transform _transform;
        GizmoInstance(const Ref<Gizmo> &gizmo, const Transform &transform);
        bool valid();

        static GizmoInstance empty;
    };

    class Gizmo {
    public:
        virtual void render(Ref<Camera> &camera, Transform& transform);
        //static MaterialPool<Material, 10> billboards;
    };
}


#endif //CPPMC_GIZMO_H
