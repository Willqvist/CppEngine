//
// Created by Gerry on 2021-05-15.
//

#include "core/scene/SceneTree.h"
#include <core/Memory.h>
#include <core/scene/Node.h>
void Ziti::SceneTree::render(Ziti::RenderEngine &engine) {

    iterate(_root,[&](Ref<Node>& node) {
        node->render(engine);
    });

}

void Ziti::SceneTree::update() {


    iterate(_root,[](Ref<Node>& node) {
        node->onUpdate();
    });

}

void Ziti::SceneTree::iterate(Ziti::Ref<Ziti::Node>& node,const std::function<void(Ref<Node> &)> &func) {
    for(auto& child : node->children()) {
        func(child);
        iterate(child,func);
    }
}

