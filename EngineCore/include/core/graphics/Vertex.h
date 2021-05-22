//
// Created by Gerry on 2020-08-13.
//

#ifndef CPPMC_VERTEX_H
#define CPPMC_VERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex {
    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec2 uv = glm::vec2(0,0);
    glm::vec3 normal = glm::vec3(0,0,0);
};
#endif //CPPMC_VERTEX_H
