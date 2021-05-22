//
// Created by Gerry on 2021-05-09.
//

#ifndef CPPMC_TRANSFORM_H
#define CPPMC_TRANSFORM_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext.hpp>
#include <functional>

namespace Ziti {
    class Transform {
    public:
        glm::vec3& position() {
            return _position;
        }
        glm::vec3& scale() {
            return _scale;
        }
        glm::vec3& rotation() {
            return _rotation;
        }

        Transform changeOfBasis(Transform& base) {
            Transform t;
            //TODO: cache forward, dont always update.
            base.setDirections();
            t._position = _position.x*base._right+_position.y*base._up+_position.z*base._forward;
            t._rotation = _rotation+base.rotation();
            t._scale = _scale*base.scale();

            return t;
        }

        void update() {
            setDirections();
        }

        glm::mat4 matrix() {
            glm::mat4 out(1.0f);
            out = glm::rotate(out, glm::radians(_rotation.x), glm::vec3(1,0,0));
            out = glm::rotate(out, glm::radians(_rotation.y), glm::vec3(0,1,0));
            out = glm::rotate(out, glm::radians(_rotation.z), glm::vec3(0,0,1));
            out = glm::translate(out, _position);
            out = glm::scale(out, _scale);
            return out;
        }

        glm::mat4 createInvMatrix() {
            glm::mat4 out(1.0f);
            out = glm::rotate(out, glm::radians(-_rotation.x), glm::vec3(1,0,0));
            out = glm::rotate(out, glm::radians(-_rotation.y), glm::vec3(0,1,0));
            out = glm::rotate(out, glm::radians(-_rotation.z), glm::vec3(0,0,1));
            out = glm::translate(out, -_position);
            out = glm::scale(out, _scale);
            return out;
        }


    private:

        void setDirections() {
            glm::mat4 inv = glm::inverse(createInvMatrix());
            _forward = glm::normalize(glm::vec3(inv[2]));
            _right = glm::normalize(glm::vec3(inv[0]));
            _up = glm::normalize(glm::vec3(inv[1]));
        }

        glm::vec3 _position = glm::vec3(0,0,0);
        glm::vec3 _scale = glm::vec3(1,1,1);
        glm::vec3 _rotation = glm::vec3(0,0,0);

        glm::vec3 _forward = glm::vec3(0,0,0);
        glm::vec3 _right = glm::vec3(0,0,0);
        glm::vec3 _up = glm::vec3(0,0,0);
    };
}


#endif //CPPMC_TRANSFORM_H
