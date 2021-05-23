//
// Created by Gerry on 2021-05-22.
//

#ifndef CPPMC_MESHGENERATOR_H
#define CPPMC_MESHGENERATOR_H

#include <core/graphics/Mesh.h>

namespace Ziti {
    class MeshGenerator {
    public:
        static Ref<Mesh> createCube(int size) {
            using namespace glm;
            Ref<Mesh> mesh = CreateRef<Mesh>();
            mesh->addVertex({vec3(-1.0f,-1.0f,-1.0f)});
            mesh->addVertex({vec3(1.0f,-1.0f,-1.0f)});
            mesh->addVertex({vec3(1.0f,-1.0f,1.0f)});
            mesh->addVertex({vec3(-1.0f,-1.0f,1.0f)});

            mesh->addVertex({vec3(-1.0f,1.0f,-1.0f)});
            mesh->addVertex({vec3(1.0f,1.0f,-1.0f)});
            mesh->addVertex({vec3(1.0f,1.0f,1.0f)});
            mesh->addVertex({vec3(-1.0f,1.0f,1.0f)});
            mesh->addIndicies({
                0,1,2,0,2,3, //bottom
                0,3,4,4,3,7, //left
                1,2,5,5,2,6, //right
                4,5,6,6,4,7, //top
                0,1,4,4,0,5, //front
                3,2,6,6,3,7 //back
            });
            mesh->upload();
            return mesh;
        }
    };
}
#endif //CPPMC_MESHGENERATOR_H
