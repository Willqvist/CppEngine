//
// Created by Gerry on 2020-08-18.
//

#include "Scene.h"
#include <core/Logger.h>
#include "components/VoxComponent.h"
#include "components/ScriptComponent.hpp"
#include "scene/Entity.hpp"
#include "components/Components.h"
#include <rendering/Renderer.h>
#include <core/Window.h>
#include <scene/components/NamedComponent.h>

VoxEng::Scene::Scene() {
}

VoxEng::Entity VoxEng::Scene::createEntity(const std::string& name, Entity& parent) {
    Entity entity(mRegistry.create(),this);
    Transform& trans = entity.addComponent<Transform>();
    trans.parentEntity = parent;
    trans.createMatrix();
    entity.addComponent<ScriptComponent>();
    NamedComponent& comp = entity.addComponent<NamedComponent>();
    comp.name(name);
    return entity;
}

VoxEng::Entity VoxEng::Scene::createEntity(const std::string &name) {
    Entity entity(mRegistry.create(),this);
    Transform& trans = entity.addComponent<Transform>();
    trans.createMatrix();
    entity.addComponent<ScriptComponent>();
    NamedComponent& comp = entity.addComponent<NamedComponent>();
    entity.addComponent<NamedComponent>();
    comp.name(name);
    return entity;
}

void VoxEng::Scene::update(Timestep ts) {
   mRegistry.view<ScriptComponent>().each([ts](ScriptComponent& comp) {
       comp.update(ts);
   });
    for(const Scope<Layer>& layer : layers) {
        layer->update(ts);
    }
}

void VoxEng::Scene::render() {
    Camera* mainCamera = nullptr;
    Transform* cameraTransform = nullptr;
    auto view = mRegistry.view<Transform, Camera>();

    for(auto entity: view) {
        auto [transformComp, camera] = view.get<Transform, Camera>(entity);
        if(camera.main) {
            mainCamera = &camera;
            cameraTransform = &transformComp;
            break;
        }
    }
    if(!mainCamera) return;
    mainCamera->update(*cameraTransform);
    Renderer::begin(mainCamera);
    mRegistry.view<ScriptComponent>().each([](ScriptComponent& comp) {
        comp.render();
    });
    for(const Scope<Layer>& layer : layers) {
        layer->render();
    }
    //Renderer::end();
}

void VoxEng::Scene::start() {
    mRegistry.view<ScriptComponent>().each([=](auto id, ScriptComponent& comp) {
        comp.build([&](VoxComponent* component) {
            component->mEntity = Entity(id,this);
            component->onCreate();
        });
    });
}

void VoxEng::Scene::stop() {
    mRegistry.each([=](auto entity) {
        mRegistry.destroy(entity);
        //comp.instance->onCreate();
    });
}

VoxEng::Scene::~Scene() {
    if(hasSceneData)
        free(data);
}

void VoxEng::Scene::onEvent(VoxEng::Event &ev) {
    EventExecutor e(ev);
    e.bind<WindowResizeEvent>(BIND_LAMBDA(onWindowResizeEvent));
}

bool VoxEng::Scene::onWindowResizeEvent(VoxEng::WindowResizeEvent &ev) {
    mRegistry.view<Camera>().each([=](auto id, Camera& comp) {
        comp.viewport = glm::vec2(ev.width,ev.height);
        comp.updateProjection();
    });
    return true;
}
