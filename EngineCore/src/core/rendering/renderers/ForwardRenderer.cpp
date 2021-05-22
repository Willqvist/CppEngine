//
// Created by Gerry on 2021-05-08.
//

#include "core/rendering/renderers/ForwardRenderer.h"
#include <core/rendering/Camera.h>
void Ziti::ForwardRenderer::init() {

}

void Ziti::ForwardRenderer::preRender() {

}

void Ziti::ForwardRenderer::render(std::vector<RenderData> tasks) {
    //TODO: sort by rendertarget, position to camera, texture and so forth.
    int wew = 0;
    for(RenderData& data : tasks) {
        if(!data.camera) continue;
        if(!data.material) continue; //TODO : set default material;
        wew ++;
        Ref<Camera> camera = data.camera;
        Transform& transform = data.transform;

        Ref<RenderTarget>& target = camera->target();
        if(target) target->bind();
        data.material->bind();
        Ref<Shader>& shader = data.material->getShader();
        shader->setUniform("transform",transform.matrix());
        shader->setUniform("view",camera->getView());
        shader->setUniform("projection",camera->getProjection());
        shader->setUniform("VP",camera->getVP());
        data.task->process(data.camera, data.material, transform);
        if(target) target->unbind();
    }
    //printf("renders!!: %d\n",wew);
}

void Ziti::ForwardRenderer::postRender() {

}
