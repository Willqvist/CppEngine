//
// Created by Gerry on 2020-08-10.
//

//#include <imgui/imgui.h>
#include <core/Logger.h>
#include <rendering/Texture.h>
#include <core/ResourceManager.h>
#include <rendering/VertexArray.h>
#include <rendering/VertexArrayRenderer.h>
#include <tools/Tools.h>
#include <rendering/Renderer.h>
#include <Scene/Scene.h>
#include <components/TestComponent.h>
#include <components/ScriptComponent.h>
#include "GameApplication.h"
static Ref<VertexArray> arrb;
static Ref<Shader> shader;
static Ref<Material> m;
static Scene* scene;
void GameApplication::init() {
    scene = new Scene();
    Ref<Entity> ent = scene->createEntity();
    ent->addScriptComponent<TestComponent>();
    Ref<VertexArray> array = VertexArray::create();
    float arr[8] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
           -0.5f, 0.5f
    };

    unsigned int indexArray[6] = {
            0,1,2,
            2,3,0
    };
    Ref<ArrayBuffer> buffer = ArrayBuffer::create(arr, 8*sizeof(float));
    Ref<IndexBuffer> ibo = IndexBuffer::create(indexArray, 6*sizeof(unsigned int));
    BufferLayout layout({
                                BufferElement(ElementType::float2)
                        });
    buffer->setLayout(layout);

    array->addBuffer(buffer);
    array->addIndexBuffer(ibo);
    arrb = array;

    shader = ResourceManager::loadShader("res/shaders/albedo.glsl");
    m = ResourceManager::createMaterial("AlbedoMaterial",shader);
    m->set("m_Vec2",2.0f);
    m->set("m_albedoTexture",ResourceManager::loadTexture("res/images/img.png"));
    m->set("m_Color",glm::vec3(1.0f,0.0f,0.0f));
}

void GameApplication::update(VoxEng::Timestep& delta) {
    scene->update(delta);
}

void GameApplication::render() {
    Renderer::render(arrb,m);
    scene->render();
}

void GameApplication::destroy() {

}

GameApplication::~GameApplication() {

}

GameApplication::GameApplication(VoxEng::WindowAttributes &attributes) : Application(attributes) {}

void GameApplication::event(VoxEng::Event &ev) {

}
