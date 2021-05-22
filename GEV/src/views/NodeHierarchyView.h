//
// Created by Gerry on 2021-05-15.
//

#ifndef CPPMC_NODEHIERARCHYVIEW_H
#define CPPMC_NODEHIERARCHYVIEW_H

#include <views/View.h>
#include <core/scene/SceneTree.h>
#include <core/scene/Node.h>
#include <core/Memory.h>
using namespace Ziti;

namespace ZitiView {
    class NodeHierarchyView : public View {
    public:

        NodeHierarchyView(Ref<SceneTree> tree);
        //void addListener(/*listener here!!*/);
        void render() override;
    private:
        int renderTree(Ref<Node>& node, int uuid);
    private:
        Ref <SceneTree> _tree;
    };
}


#endif //CPPMC_NODEHIERARCHYVIEW_H
