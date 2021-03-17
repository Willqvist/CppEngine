//
// Created by Gerry on 2021-03-16.
//
#include "Registry.h"

Registry::Registry(entt::registry &registry) : registry(registry) {}

template<class T>
T &Registry::get(entt::entity entity) {
    return registry.get<T>(entity);
}

template<class T>
bool Registry::has(entt::entity entity) {
    return registry.has<T>(entity);
}

bool Registry::valid(entt::entity entity){
    return registry.valid(entity);
}

entt::registry &Registry::core() {
    return registry;
}