//
// Created by Gerry on 2021-05-08.
//

#ifndef CPPMC_MESH_H
#define CPPMC_MESH_H

#include <vector>
#include "Vertex.h"
#include "VertexArray.h"
#include "Buffer.h"

namespace Ziti {
    class Mesh {
    public:
        Mesh();
        void addVertex(const Vertex& vertex);
        void addVerticies(std::vector<Vertex>& verticies);
        Vertex& vertexAt(int index);
        void upload();
        void render();
    private:
        std::vector<float> _data;
        Ref<VertexArray> _vao;
        BufferLayout _layout;

    };
}


#endif //CPPMC_MESH_H
