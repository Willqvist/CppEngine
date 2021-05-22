//
// Created by Gerry on 2021-05-08.
//

#include <core/utils/Time.h>
#include "TestViewApp.h"
#include <stdio.h>
#include <core/rendering/RenderTask.h>
#include <core/graphics/Shader.h>
#include <core/loaders/GraphicsLoader.h>
#include <core/graphics/textures/RenderableTexture.h>
#include <core/scene/Spatial.h>
#include <core/scene/Camera3D.h>

using namespace Ziti;
void TestViewApp::start() {
    _cube = new CubeTest();
    ShaderLayout layout({
            {"position",0}
    });
    _mat = Material::create(GraphicsLoader::loadShader("test.shader"));
    _mat2 = Material::create(GraphicsLoader::loadShader("test2.shader"));
    Ref<Texture> tes = GraphicsLoader::loadTexture("tes.png");
    //printf("wew: %d\n", tes == nullptr);
    _rtex = CreateRef<RenderableTexture>(FBOBuffers::COLOR | FBOBuffers::DEPTH, 1980/10,1080/10);
    _camera = CreateRef<Camera>(window());
    _cam2 = CreateRef<Camera>(_rtex);

    _mat2->set("_mainTexture",_rtex);
    _mat->set("_mainTexture",tes);
    _cam2->transform().position().z = -5;
    _cam2->transform().position().y = 0;
    _cam2->transform().position().x = 0;
    _cam2->update();

    _camera->transform().position().z = -15;
    _camera->transform().position().y = 0;
    _camera->transform().position().x = 0;
    _camera->update();
    /*
    SceneNode node = getNodeTree()->add("test",nullptr);
    SceneNode node2 = getNodeTree()->add("test",nullptr);
    node->add("wew",nullptr);
    node2->add("wew3",nullptr);
     */
    Ref<Spatial> spat = getNodeTree()->root()->addNode<Spatial>();
    Ref<Camera3D> cam = getNodeTree()->root()->addNode<Camera3D>();
    spat->addNode<Spatial>();
    cam->addNode<Spatial>();
    _cameraNode = getNodeTree()->root()->findFirst<Camera3D>();
    _cameraNode->internal()->setTarget(window());
    _cameraNode->internal()->transform().position().z = -5;
}

void TestViewApp::update() {
    getNodeTree()->update();
    //printf("im here updating!!!\n");

}

void TestViewApp::render(RenderEngine &engine) {
    //engine.setCamera(_cameraNode->internal());
    //_cam2->transform().position().z -= 1;
    //_cam2->update();
    /*
    RenderData data2;
    data2.task = _cube;
    data2.material = _mat;
    data2.camera = _cam2;
    engine.addRenderTask(data2);
*/
    RenderData data;
    data.task = _cube;
    data.material = _mat;
    data.camera = _cameraNode->internal();
    engine.addRenderTask(data);

    getNodeTree()->render(engine);

}

void TestViewApp::stop() {

}
