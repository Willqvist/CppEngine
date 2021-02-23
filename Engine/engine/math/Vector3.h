//
// Created by Gerry on 2020-08-25.
//

#ifndef CPPMC_VECTOR3_H
#define CPPMC_VECTOR3_H

#include <glm/vec3.hpp>

class Vector3 {
public:
    inline static const glm::vec3& up() {
        return upVec;
    }
    inline static const glm::vec3& right() {
        return rightVec;
    }
    inline static const glm::vec3& forward() {
        return forwardVec;
    }
private:
    inline static const glm::vec3 upVec = glm::vec3(0,1,0);
    inline static const glm::vec3 rightVec = glm::vec3(1,0,0);
    inline static const glm::vec3 forwardVec = glm::vec3(0,0,1);
};
#endif //CPPMC_VECTOR3_H
