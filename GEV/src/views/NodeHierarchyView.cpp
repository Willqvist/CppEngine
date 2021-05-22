//
// Created by Gerry on 2021-05-15.
//

#include <imgui/imgui.h>
#include "NodeHierarchyView.h"
#include <core/scene/Node.h>
void ZitiView::NodeHierarchyView::render() {
    ImGui::Begin("Hierarchy");
    //Ref<TreeNode<Ref<Node>>> node = _tree;
    Ref<Node>& root = _tree->root();
    renderTree(root,0);
    ImGui::End();
}

ZitiView::NodeHierarchyView::NodeHierarchyView(Ref<SceneTree> tree) : _tree(tree) {

}

int ZitiView::NodeHierarchyView::renderTree(Ref<Node>& node,int uuid) {

    for(Ref<Node>& child : node->children()) {
        uuid ++;
        unsigned int flags = ImGuiTreeNodeFlags_OpenOnArrow;
        bool isLeafNode = child->children().size() == 0;
        if(isLeafNode) {
            flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        }
        ImGui::PushID(uuid);
        bool open = ImGui::TreeNodeEx(child->getClass().c_str(), flags);
        ImGui::PopID();
        if(!isLeafNode && open) {
            uuid = renderTree(child,uuid);
            ImGui::TreePop();
        }
    }
    return uuid;
}
