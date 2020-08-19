//
// Created by Gerry on 2020-08-18.
//

#include "Renderer.h"
#include "VertexArrayRenderer.h"

void VoxEng::Renderer::begin() {

}

void VoxEng::Renderer::render(/*const ComponentRef<Transform>& transform,*/VoxEng::Ref<VoxEng::VertexArray> data, VoxEng::Ref<VoxEng::Material> material) {
    material->bind();
    //material->getShader()->setUniform("m_viewProj",camera->viewProjection());
    //material->getShader()->setUniform("m_transform",transform->matrix());
    VertexArrayRenderer::draw(data);
}

void VoxEng::Renderer::end() {

}
