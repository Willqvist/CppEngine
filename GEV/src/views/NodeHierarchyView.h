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

    class HierarchyListener {
    public:
        virtual void nodeActive(Ref<Node>& active) = 0;
        virtual ~HierarchyListener() = default;
    };

    class NodeHierarchyView : public View {
    public:

        NodeHierarchyView(Ref<SceneTree> tree);
        void addListener(Ref<HierarchyListener> listener);
        void render() override;
    private:
        int renderTree(Ref<Node>& node, int uuid);
    private:
        Ref <SceneTree> _tree;
        std::vector<Ref<HierarchyListener>> _listeners;
    };
}


#endif //CPPMC_NODEHIERARCHYVIEW_H
