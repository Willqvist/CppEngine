//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_COMPONENTS_H
#define CPPMC_COMPONENTS_H

#include <glm/mat4x4.hpp>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "core/Logger.h"
#include "Transform.h"
#include <glm/gtx/string_cast.hpp>
#include <math.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <math/Vector3.h>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
namespace VoxEng {

    struct ParentTransform {};

    enum class ProjectionMode {
        PERSPECTIVE=0, ORTHOGRAPHIC
    };

    struct Camera {
        glm::mat4 view,proj,viewProj;
        ProjectionMode mode;
        float fov = 70.0f;
        float zNear = 0.01f;
        float zFar = 1000.0f;
        glm::vec2 viewport = glm::vec2(1080,720);
        Camera() {
            projection(ProjectionMode::PERSPECTIVE);
        }

        void updateProjection() {
            projection(this->mode);
        }

        void projection(ProjectionMode mode) {
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

        void update(Transform& transform) {
            view = glm::mat4(1.0f);
            view = glm::rotate(view, glm::radians(transform.rotation().x),glm::vec3(-1.0f,0,0));
            view = glm::rotate(view, glm::radians(transform.rotation().y),glm::vec3(0,-1.0f,0));
            view = glm::rotate(view, glm::radians(transform.rotation().z),glm::vec3(0,0,-1.0f));
            view = glm::translate(view,-transform.position());
            viewProj = proj*view;
        }

        bool main = true;
    };

}

#endif //CPPMC_COMPONENTS_H
