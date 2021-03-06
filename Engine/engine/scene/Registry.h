//
// Created by Gerry on 2020-08-26.
//

#ifndef CPPMC_REGISTRY_H
#define CPPMC_REGISTRY_H

#include <entt/entity/registry.hpp>

class Registry {

public:
    Registry(entt::registry& registry);

    template<class T>
    T& get(entt::entity entity);

    template<class T>
    bool has(entt::entity entity);

    bool valid(entt::entity entity);

    entt::registry& core();

private:
    entt::registry & registry;
};
#endif //CPPMC_REGISTRY_H
