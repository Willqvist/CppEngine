//
// Created by Gerry on 2020-08-18.
//

#include "Renderer.h"
#include "VertexArrayRenderer.h"

void VoxEng::Renderer::begin(Camera* camera) {
    Renderer::camera = camera;
}

void VoxEng::Renderer::render(VoxEng::Ref<VoxEng::VertexArray> data, VoxEng::Ref<VoxEng::Material> material,Transform& transform) {
    material->bind();
    material->getShader()->setUniform("uViewProj",camera->viewProj);
    material->getShader()->setUniform("uTransform",transform);
    VertexArrayRenderer::draw(data);

}

void VoxEng::Renderer::end() {

}
