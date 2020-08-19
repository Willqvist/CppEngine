//
// Created by Gerry on 2020-08-13.
//

#ifndef CPPMC_VERTEX_H
#define CPPMC_VERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};
#endif //CPPMC_VERTEX_H
