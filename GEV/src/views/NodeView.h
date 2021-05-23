//
// Created by Gerry on 2021-05-23.
//

#ifndef CPPMC_NODEVIEW_H
#define CPPMC_NODEVIEW_H

#include <views/View.h>
#include <core/scene/Node.h>
#include "NodeHierarchyView.h"

using namespace Ziti;
namespace ZitiView {
    class NodeView : public View, public HierarchyListener, public AttributeVisitor {
    public:
        void setNode(Ref<Node>& node);

        void nodeActive(Ref<Node> &active) override;

        void visit(const std::string &name, glm::vec3 *value) override;

        void visit(const std::string &name, glm::vec2 *value) override;

        void visit(const std::string &name, int *value) override;

        void visit(const std::string &name, float *value) override;

        void visit(const std::string &name, bool *value) override;

        void visit(const std::string &name, Transform *value) override;

        void visit(const std::string &name, std::string *value) override;

        void render() override;


    private:
        Ref<Node> _node;
    };
}


#endif //CPPMC_NODEVIEW_H
