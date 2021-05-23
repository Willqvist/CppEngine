//
// Created by Gerry on 2021-05-08.
//

#ifndef CPPMC_CAMERA_H
#define CPPMC_CAMERA_H

#include "RenderTarget.h"
#include <core/Memory.h>
#include <glm/mat4x4.hpp>
#include <core/Transform.h>

namespace Ziti {

    enum class ProjectionType {
        PERSPECTIVE, ORTHOGRAPHIC
    };

    class Camera {
    public:

        Camera();

        Camera(Ref<RenderTarget> target) : _target(target) {
            updateProjection();
        }

        Ref<RenderTarget>& target()  {
            return _target;
        };

        void setTarget(Ref<RenderTarget> target) {
            _target = target;
            updateProjection();
        };

        Transform& transform() {
            return _transform;
        }

        void setTransform(const Transform& t) {
            _transform = t;
        }

        void setProjection(ProjectionType type);

        void clear();

        void update();

        glm::mat4 getVP();

        glm::mat4 getView();

        glm::mat4 getProjection();

    private:
        void updateProjection();
        Ref<RenderTarget> _target;
        ProjectionType _type = ProjectionType::PERSPECTIVE;
        glm::mat4 _projection = glm::mat4(1.0f),_view = glm::mat4(1.0f), _viewProj;
        bool _dirty = true;
        Transform _transform;
    };
}


#endif //CPPMC_CAMERA_H
