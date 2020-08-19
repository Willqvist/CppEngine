//
// Created by Gerry on 2020-08-18.
//

#ifndef CPPMC_SCENE_H
#define CPPMC_SCENE_H

#include <entt/entt.hpp>
#include "Entity.hpp"
#include <core/Core.h>
#include <vector>
#include <core/Timestep.h>

namespace VoxEng {
    class Scene {
    public:
        Scene();

        Ref<Entity> createEntity();

        void update(Timestep ts);

        void render();

        std::vector<Ref<Entity>>& entities();

        ~Scene();

    private:
        entt::registry mRegistry;
        std::vector<Ref<Entity>> mEntities;
        friend class Entity;
    };
}


#endif //CPPMC_SCENE_H
