//
// Created by Gerry on 2020-08-25.
//

#ifndef CPPMC_VECTOR3_H
#define CPPMC_VECTOR3_H

#include <glm/vec3.hpp>

class Vector3 {
public:
    static const glm::vec3 const& up() {
        return upVec;
    }
    static const glm::vec3 const& right() {
        return rightVec;
    }
    static const glm::vec3 const& forward() {
        return forwardVec;
    }
private:
    inline static const glm::vec3 upVec = glm::vec3(0,1,0);
    inline static const glm::vec3 rightVec = glm::vec3(1,0,0);
    inline static const glm::vec3 forwardVec = glm::vec3(0,0,1);
};
#endif //CPPMC_VECTOR3_H
