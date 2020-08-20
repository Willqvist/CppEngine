//
// Created by Gerry on 2020-08-18.
//

#include "Renderer.h"
#include "VertexArrayRenderer.h"

void VoxEng::Renderer::begin(Camera* camera) {
    Renderer::camera = camera;
}

void VoxEng::Renderer::render(/*const ComponentRef<Transform>& transform,*/VoxEng::Ref<VoxEng::VertexArray> data, VoxEng::Ref<VoxEng::Material> material) {
    material->bind();
    material->getShader()->setUniform("uViewProj",camera->viewProj);
    //material->getShader()->setUniform("uTransform",camera.proj);
    VertexArrayRenderer::draw(data);
}

void VoxEng::Renderer::end() {

}
