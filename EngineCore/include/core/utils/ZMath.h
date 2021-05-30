//
// Created by Gerry on 2021-05-29.
//

#ifndef CPPMC_ZMATH_H
#define CPPMC_ZMATH_H

#include <glm/vec3.hpp>

namespace Ziti {
    class ZMath {
    public:
        static inline glm::vec3 lerp(glm::vec3 x, glm::vec3 y, float t) {
            return x * (1.f - t) + y * t;
        }
    };
}
#endif //CPPMC_ZMATH_H
