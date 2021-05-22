//
// Created by Gerry on 2021-05-08.
//

#ifndef CPPMC_CUBETEST_H
#define CPPMC_CUBETEST_H

#include <core/rendering/RenderTask.h>
#include <core/graphics/Mesh.h>
#include <core/graphics/Shader.h>
#include <core/graphics/Material.h>
#include <core/Transform.h>
class CubeTest : public Ziti::RenderTask {
public:
    CubeTest() {
        _mesh = new Ziti::Mesh();
        const float a = 1.0f;
        _mesh->addVertex({glm::vec3(-a,a,0),glm::vec2(0,1)});
        _mesh->addVertex({glm::vec3(a,a,0),glm::vec2(1,1)});
        _mesh->addVertex({glm::vec3(a,-a,0),glm::vec2(1,0)});

        _mesh->addVertex({glm::vec3(-a,a,0),glm::vec2(0,1)});
        _mesh->addVertex({glm::vec3(-a,-a,0),glm::vec2(0,0)});
        _mesh->addVertex({glm::vec3(a,-a,0),glm::vec2(1,0)});

        _mesh->upload();
    }
    void process(Ziti::Ref<Ziti::Camera> &camera, Ziti::Ref<Ziti::Material> &material, Ziti::Transform &transform) override {
        _mesh->render();
    }
private:
    Ziti::Mesh* _mesh;
};
#endif //CPPMC_CUBETEST_H

