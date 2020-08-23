//
// Created by Gerry on 2020-08-19.
//

#ifndef CPPMC_COMPONENTS_H
#define CPPMC_COMPONENTS_H

#include <glm/mat4x4.hpp>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "core/Logger.h"
#include <glm/gtx/string_cast.hpp>
#include <math.h>
#include <glm/mat4x4.hpp>
namespace VoxEng {
    class Transform {
    public:
        glm::vec3 position = glm::vec3(0,0,0);
        glm::vec3 rotation = glm::vec3(0,0,0);
        glm::vec3 scale = glm::vec3(1,1,1);
        Transform* parent;

        glm::vec3 forward() {
            return glm::normalize(glm::vec3(sin(glm::radians(rotation.y)),sin(glm::radians(rotation.x)),cos(glm::radians(rotation.y))));
        }

        glm::vec3 right() {
            return glm::normalize(glm::vec3(sin(glm::radians(rotation.y-90)),sin(glm::radians(rotation.x)),cos(glm::radians(rotation.y-90))));
        }

        glm::vec3 up() {
            //float sinX = sin(glm::radians(rotation.x));
            return glm::vec3(0,1,0);
        }

        operator glm::mat4 () const {
            glm::mat4 id = glm::mat4(1.0f);
            id = glm::translate(id,position);
            id = glm::rotate(id,rotation.x,glm::vec3(1.0f,0,0));
            id = glm::rotate(id,rotation.y,glm::vec3(0,1.0f,0));
            id = glm::rotate(id,rotation.z,glm::vec3(0,0,1.0f));
            id = glm::scale(id,scale);
            return id;
        }
    };

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
            DEBUG_LOG("Creating camera");
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
            view = glm::rotate(view, glm::radians(transform.rotation.x),glm::vec3(-1.0f,0,0));
            view = glm::rotate(view, glm::radians(transform.rotation.y),glm::vec3(0,-1.0f,0));
            view = glm::rotate(view, glm::radians(transform.rotation.z),glm::vec3(0,0,-1.0f));
            view = glm::translate(view,-transform.position);
            viewProj = proj*view;
        }

        bool main = true;
    };

    class NamedComponent {
    public:
        std::string mName,mTag;
        unsigned int id;
        NamedComponent() {
            id = globalId ++;
        }
        void name(const std::string& name) {
            this->mName = name;
        }

        std::string& name() {
            return mName;
        }

    private:
        inline static int globalId = 0;
    };

}

#endif //CPPMC_COMPONENTS_H
