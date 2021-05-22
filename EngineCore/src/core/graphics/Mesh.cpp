//
// Created by Gerry on 2021-05-08.
//

#include "core/graphics/Mesh.h"
#include <core/graphics/Buffer.h>
#include <core/graphics/VertexArrayRenderer.h>

Ziti::Mesh::Mesh() : _layout(BufferLayout({
    ElementType::float3,
    ElementType::float3,
    ElementType::float2
})) {
    _vao = VertexArray::create();
}

void Ziti::Mesh::addVertex(const Vertex &vertex) {
    _data.push_back(vertex.position.x);
    _data.push_back(vertex.position.y);
    _data.push_back(vertex.position.z);
    _data.push_back(vertex.normal.x);
    _data.push_back(vertex.normal.y);
    _data.push_back(vertex.normal.z);
    _data.push_back(vertex.uv.x);
    _data.push_back(vertex.uv.y);
}

void Ziti::Mesh::addVerticies(std::vector<Vertex> &verticies) {
    for(auto& vert : verticies) {
        addVertex(vert);
    }
}

Vertex &Ziti::Mesh::vertexAt(int index) {
    int rlIdx = index*(3+3+2);
    Vertex v;
    //TODO, fix!
    return v;
}

void Ziti::Mesh::upload() {
    _vao = VertexArray::create();
    Ref<ArrayBuffer> data = ArrayBuffer::create(_data.data(),_data.size());
    data->setLayout(_layout);
    _vao->addBuffer(data);
}

void Ziti::Mesh::render() {
    VertexArrayRenderer::draw(_vao, RenderMode::TRIANGLES);
}
