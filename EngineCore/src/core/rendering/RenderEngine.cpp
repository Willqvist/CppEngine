//
// Created by Gerry on 2021-05-07.
//

#include "core/rendering/RenderEngine.h"

void Ziti::RenderEngine::setRenderer(Ziti::Ref<Ziti::Renderer> renderer) {
    _renderer = renderer;
    _renderer->init();
}

void Ziti::RenderEngine::setCamera(Ziti::Ref<Ziti::Camera> camera) {
    _camera = camera;
}

void Ziti::RenderEngine::addRenderTask(Ziti::RenderData& data) {
    //TODO: sort by shader program and camera. different weights!
    //each camera get each list of object sorted by distance to camera to minimize overdraw.
    //cull objects that are outside of camera, each rendertask need to have a bound volume! f.ex. isInsideFrustum()
    data.camera = data.camera ? data.camera : _camera;
    if(!_cameras.contains(data.camera)) {
        _cameras.insert(data.camera);
    }
    _tasks.push_back(data);
}

void Ziti::RenderEngine::flush() {
    if(!_renderer) {
        _tasks.clear();
        _cameras.clear();
        return;
    }

    _renderer->preRender();
    for(auto& cam : _cameras) {
        cam->target()->bind();
        cam->clear();
        cam->target()->unbind();
    }
    _renderer->render(_tasks);
    _renderer->render(_camera, _gizmos);
    _renderer->postRender();
    _tasks.clear();
    _cameras.clear();

}

void Ziti::RenderEngine::addGizmoRenderTask(Ziti::GizmoInstance &data) {
    if(data.valid())
        _gizmos.push_back(data);
}
