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
#include <core/scene/MeshRenderer.h>
#include <core/utils/MeshGenerator.h>

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
    //_cam2 = CreateRef<Camera>(_rtex);

    //_mat2->set("_mainTexture",_rtex);
    _mat->set("_mainTexture",tes);
    //_cam2->transform().position().z = -5;
    //_cam2->transform().position().y = 0;
    //_cam2->transform().position().x = 0;
    //_cam2->update();

    /*
    SceneNode node = getNodeTree()->add("test",nullptr);
    SceneNode node2 = getNodeTree()->add("test",nullptr);
    node->add("wew",nullptr);
    node2->add("wew3",nullptr);
     */
    Ref<Spatial> spat = getNodeTree()->root()->addNode<Spatial>();
    Ref<MeshRenderer> rend = spat->addNode<MeshRenderer>();
    rend->setMesh(MeshGenerator::createCube(1));
    rend->setMaterial(_mat);
    Ref<Spatial> spat2 = spat->addNode<Spatial>();
    Ref<Camera3D> cam = spat2->addNode<Camera3D>();

    _cameraNode = getNodeTree()->root()->findFirst<Camera3D>();
    _cameraNode->internal()->setTarget(window());
    _cameraNode->local().position().z = -5;
    _cameraNode->local().position().x = -5;
}

void TestViewApp::update() {
    getNodeTree()->update();
    //printf("im here updating!!!\n");

}

void TestViewApp::render(RenderEngine &engine) {
    engine.setCamera(_cameraNode->internal());
    /*
    RenderData data;
    data.task = _cube;
    data.material = _mat;
    engine.addRenderTask(data);
*/
    getNodeTree()->render(engine);

}

void TestViewApp::renderGizmos(RenderEngine &engine) {
    getNodeTree()->renderGizmos(engine);
}

void TestViewApp::stop() {

}
