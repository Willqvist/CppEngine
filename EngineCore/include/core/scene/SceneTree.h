//
// Created by Gerry on 2021-05-15.
//

#ifndef CPPMC_SCENETREE_H
#define CPPMC_SCENETREE_H

#include <string>
#include <core/utils/Tree.h>

#include <core/Memory.h>
#include <core/rendering/RenderEngine.h>
#include "Node.h"
#include <functional>
namespace Ziti {

    class RootNode : public Node {
        ISCLASS(RootNode,Node)
    };

    class SceneTree {
    public:

        SceneTree() {
            _root = CreateRef<RootNode>();
            _root->setSceneTree(this);
        }

        Ref<Node>& root() {
            return _root;
        }

        void render(RenderEngine& engine);
        void renderGizmos(RenderEngine& engine);
        void update();
    private:
        void iterate(Ref<Node>& node,const  std::function<void(Ref<Node>&)>& func);
        Ref<Node> _root;
    };
}


#endif //CPPMC_SCENETREE_H
