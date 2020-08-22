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
#include <scene/components/TestComponent.hpp>
#include <scene/components/ScriptComponent.hpp>
#include "GameApplication.h"
#include "components/CameraMovement.h"

static Ref<VertexArray> arrb;
static Ref<Shader> shader;
static Ref<Material> m;
void GameApplication::init() {
    Ref<Scene> scene = Scene::create("test");
    Scene::goToScene("test",nullptr,0);
    Entity ent = scene->createEntity("testObject");
    //ent->addComponent<ScriptComponent>().bind<TestComponent>();
    Instansiator::addScriptComponent<CameraMovement>(ent);
    Camera& cam = ent.addComponent<Camera>();
    Ref<Window> window = getWindow();
    cam.viewport = glm::vec2(window->width(),window->height());
    cam.updateProjection();
    Transform& transform = ent.getComponent<Transform>();
    transform.position.z += 10.0f;
    cam.update(transform);
    //ent.addScriptableComponent<TestComponent>();
    scene->start();
    Ref<VertexArray> array = VertexArray::create();
    float arr[8] = {
            -1.5f, -1.5f,
            1.5f, -1.5f,
            1.5f, 1.5f,
           -1.5f, 1.5f
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
    m->set("m_Color",glm::vec3(1.0f,1.0f,0.0f));
}

void GameApplication::update(VoxEng::Timestep& delta) {
    Scene::active()->update(delta);
}

void GameApplication::render() {
    Scene::active()->render();
    Renderer::render(arrb,m);
    Renderer::end();
}

void GameApplication::destroy() {
    //scene->stop();
}

GameApplication::~GameApplication() {

}

GameApplication::GameApplication(VoxEng::WindowAttributes &attributes) : Application(attributes) {}

void GameApplication::event(VoxEng::Event &ev) {

}
