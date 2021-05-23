//
// Created by Gerry on 2021-05-22.
//

#include "core/scene/MeshRenderer.h"
using namespace glm;
void Ziti::MeshRenderer::render(Ziti::RenderEngine &engine) {
    Spatial::render(engine);
    if(_mesh) {
        RenderData data;
        data.task = (RenderTask*)this;
        data.material = _material;
        data.transform = global();
        engine.addRenderTask(data);
    }
}

void Ziti::MeshRenderer::start() {
    Spatial::start();
}

void Ziti::MeshRenderer::setMesh(const Ziti::Ref<Ziti::Mesh> &mesh) {
    _mesh = mesh;
}

void Ziti::MeshRenderer::process(Ziti::Ref<Ziti::Camera> &camera, Ziti::Ref<Ziti::Material> &material,
                                 Ziti::Transform &transform) {
    _mesh->render();
}

void Ziti::MeshRenderer::setMaterial(Ziti::Ref<Ziti::Material> &mat) {
    _material = mat;
}
