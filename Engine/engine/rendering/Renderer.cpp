//
// Created by Gerry on 2020-08-18.
//

#include "Renderer.h"
#include "VertexArrayRenderer.h"
#include <scene/components/Components.h>
#include "VertexArray.h"
#include "scene/components/Transform.h"
#include <core/Material.h>

void VoxEng::Renderer::begin(Camera* camera) {
    Renderer::camera = camera;
}

void VoxEng::Renderer::pushMode(RenderMode mode)
{
    _mode.push(mode);
}


void VoxEng::Renderer::popMode()
{
    _mode.pop();
}

void VoxEng::Renderer::render(VoxEng::Ref<VoxEng::VertexArray> data, VoxEng::Ref<VoxEng::Material> material,Transform& transform) {
    material->bind();
    material->getShader()->setUniform("uViewProj",camera->viewProj);
    material->getShader()->setUniform("uTransform",transform);
    VertexArrayRenderer::draw(data,_mode.top());

}

void VoxEng::Renderer::end() {

}

VoxEng::Camera* VoxEng::Renderer::camera = nullptr;
std::stack<VoxEng::RenderMode> VoxEng::Renderer::_mode  = std::stack<VoxEng::RenderMode>({TRIANGLES});
