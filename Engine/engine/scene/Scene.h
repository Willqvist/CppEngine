//
// Created by Gerry on 2020-08-18.
//

#ifndef CPPMC_SCENE_H
#define CPPMC_SCENE_H

#include <entt/entt.hpp>
#include <core/Core.h>
#include <vector>
#include <core/Timestep.h>
#include <map>
#include <string.h>
#include <event/EventListener.h>
#include <core/Application.h>
#include <vector>
#include <thread>
#include "Layer.h"
#include "Registry.h"

namespace VoxEng {

    class Entity;

    class Scene: public EventListener {
    public:
        Scene();

        Entity createEntity(const std::string& name);
        Entity createEntity(const std::string& name, Entity& parent);

        void update(Timestep ts);

        void render();

        void start();

        void stop();

        Registry registry() {
            return Registry(mRegistry);
        }

        void onEvent(Event &ev) override;

        template<class T>
        T* sceneData() {
            return reinterpret_cast<T*>(data);
        };
        template<class T>
        void addLayer() {
            Scope<Layer> layer = CreateScope<T>();
            layer->onCreate();
            layers.push_back(std::move(layer));
        }

        static Ref<Scene> create(const std::string& name) {
            Ref<Scene> scene = CreateRef<Scene>();
            scene->application = Application::getApplication();
            Application::getApplication()->getWindow()->addEventListener(scene);
            scenes[name] = scene;
            return scene;
        };

        template<class T>static Ref<Scene> create(const std::string& name) {
            Ref<Scene> scene = CreateRef<T>();
            scene->application = Application::getApplication();
            Application::getApplication()->getWindow()->addEventListener(scene);
            scenes[name] = scene;
            return scene;
        };

        virtual void onSceneStart(void* data) {};

        virtual void onSceneEnd() {};

        static Ref<Scene> goToScene(const std::string& name, void* data, int size) {
            if(activeScene) {
                activeScene->onSceneEnd();
            }
            activeScene = scenes[name];
            activeScene->onSceneEnter(data,size);
            activeScene->start();
            return activeScene;
        };

        static Ref<Scene> active() {
            return activeScene;
        };

        ~Scene();
    protected:
        Application* application;
    private:
        std::vector<Scope<Layer>> layers;
        bool onWindowResizeEvent(WindowResizeEvent& ev);
        void onSceneEnter(void* data, int size) {
            if(hasSceneData) {
                free(data);
            }
            this->data = nullptr;
            if(size > 0) {
                void *newData = malloc(size);
                memcpy(newData, data, size);
                this->data = data;
                hasSceneData = true;
            }
            onSceneStart(this->data);
        }

        entt::registry mRegistry;
        void* data;
        bool hasSceneData = false;
        inline static Ref<Scene> activeScene = nullptr;
        inline static std::map<std::string, Ref<Scene>> scenes;
        friend class Entity;
    };
}


#endif //CPPMC_SCENE_H
