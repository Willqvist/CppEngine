//
// Created by Gerry on 2020-08-18.
//

#ifndef CPPMC_SCENE_H
#define CPPMC_SCENE_H

#include <entt/entt.hpp>
#include <core/Core.h>
#include <vector>
#include <map>
#include <string.h>
#include <event/EventListener.h>
#include <vector>
#include <thread>
#include "Registry.h"
#include "Layer.h"
namespace VoxEng {

    class Entity;
    class Application;
    class WindowResizeEvent;
    class Timestep;

    class Scene: public EventListener {
    public:
        Scene();

        Entity createEntity(const std::string& name);
        Entity createEntity(const std::string& name, Entity& parent);

        void update(Timestep ts);

        void render();

        void start();

        void stop();

        Registry registry();

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

        //static Ref<Scene> create(const std::string& name);

        template<class T>
        static Ref<Scene> create(const std::string& name) {
            Ref<Scene> scene = CreateRef<T>();
            scene->application = Application::getApplication();
            Application::getApplication()->getWindow()->addEventListener(scene);
            scenes[name] = scene;
            return scene;
        }

        virtual void onSceneStart(void* data);

        virtual void onSceneEnd();

        static Ref<Scene> goToScene(const std::string& name, void* data, int size);
        static Ref<Scene> active();

        ~Scene();
    protected:
        Application* application;
    private:
        std::vector<Scope<Layer>> layers;
        bool onWindowResizeEvent(WindowResizeEvent& ev);
        void onSceneEnter(void* data, int size);

        entt::registry mRegistry;
        void* data;
        bool hasSceneData = false;
        static Ref<Scene> activeScene;
        static std::map<std::string, Ref<Scene>> scenes;
        friend class Entity;
    };
}


#endif //CPPMC_SCENE_H
