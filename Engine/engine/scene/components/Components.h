//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_COMPONENTS_H
#define CPPMC_COMPONENTS_H

#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "core/Logger.h"
#include <glm/gtx/string_cast.hpp>
#include <math.h>
#include <glm/mat4x4.hpp>
namespace VoxEng {

    class Transform;

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
        Camera();

        void updateProjection();

        void projection(ProjectionMode mode);

        void update(Transform& transform);

        bool main = true;
    };

}

#endif //CPPMC_COMPONENTS_H
