//
// Created by Gerry on 2020-08-18.
//

#ifndef CPPMC_SCENE_H
#define CPPMC_SCENE_H

#include <entt/entt.hpp>
#include <core/Core.h>
#include <vector>
#include <core/Timestep.h>
#include <scene/components/Components.h>
#include <map>
#include <string.h>
#include <event/EventListener.h>
#include <core/Application.h>
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

        void onEvent(Event &ev) override;

        template<class T>
        T* sceneData() {
            return reinterpret_cast<T*>(data);
        };

        std::vector<Entity>& entities();

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



        static Ref<Scene> goToScene(const std::string& name, void* data, int size) {
            activeScene = scenes[name];
            if(size > 0)
                activeScene->onSceneEnter(data,size);
            return activeScene;
        };

        static Ref<Scene> active() {
            return activeScene;
        };

        ~Scene();
    protected:
        Application* application;
    private:
        bool onWindowResizeEvent(WindowResizeEvent& ev);
        void onSceneEnter(void* data, int size) {
            if(hasSceneData) {
                free(data);
            }
            void* newData = malloc(size);
            memcpy(newData, data,size);
            this->data = data;
            hasSceneData = true;
        }

        entt::registry mRegistry;
        void* data;
        bool hasSceneData = false;
        std::vector<Entity> mEntities;
        inline static Ref<Scene> activeScene;
        inline static std::map<std::string, Ref<Scene>> scenes;
        friend class Entity;
    };
}


#endif //CPPMC_SCENE_H
