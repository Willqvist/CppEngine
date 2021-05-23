//
// Created by Gerry on 2021-05-23.
//

#include <imgui/imgui.h>
#include "NodeView.h"

void ZitiView::NodeView::render() {

    ImGui::Begin("Inspector");
    if(!_node) {
        ImGui::End();
        return;
    }
    ImGui::Text("Node: %s",_node->getClass().c_str());
    Attributes a(this);
    _node->attributes(a);
    a.visitAll();
    ImGui::End();

}

void ZitiView::NodeView::setNode(Ref<Node> &node) {
    _node = node;
}

void ZitiView::NodeView::nodeActive(Ref<Node> &active) {
    setNode(active);
}

void ZitiView::NodeView::visit(const std::string &name, glm::vec3 *value) {
    printf("IM HERE!!! %f\n",value->x);
    value->x += 2;
}

void ZitiView::NodeView::visit(const std::string &name, glm::vec2 *value) {

}

void ZitiView::NodeView::visit(const std::string &name, int *value) {

}

void ZitiView::NodeView::visit(const std::string &name, float *value) {

}

void ZitiView::NodeView::visit(const std::string &name, bool *value) {

}

void ZitiView::NodeView::visit(const std::string &name, std::string *value) {

}

void ZitiView::NodeView::visit(const std::string &name, Transform *value) {
    //printf("IM HERE!!! %f\n",value->position().x);
    //value->position().x += 2;
    glm::vec3& pos = value->position();
    ImGui::BeginGroup();
    ImGui::InputFloat("X",&pos.x,0.01f);
    ImGui::InputFloat("Y",&pos.y,0.01f);
    ImGui::InputFloat("Z",&pos.z,0.01f);
    ImGui::EndGroup();
}
