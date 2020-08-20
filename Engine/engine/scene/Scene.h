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

namespace VoxEng {

    class Entity;

    class Scene {
    public:
        Scene();

        Entity createEntity(const std::string& name);
        Entity createEntity(const std::string& name, Entity& parent);

        void update(Timestep ts);

        void render();

        void start();

        void stop();

        std::vector<Entity>& entities();

        ~Scene();

    private:
        entt::registry mRegistry;
        std::vector<Entity> mEntities;
        friend class Entity;
    };
}


#endif //CPPMC_SCENE_H
