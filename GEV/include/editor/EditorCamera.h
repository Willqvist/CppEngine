//
// Created by Gerry on 2021-05-26.
//

#ifndef CPPMC_EDITORCAMERA_H
#define CPPMC_EDITORCAMERA_H


#include <core/rendering/RenderTarget.h>
#include <glm/vec3.hpp>
#include <core/Memory.h>
#include <core/rendering/Camera.h>
#include "../../src/views/NodeHierarchyView.h"

using namespace Ziti;

namespace ZitiView {
    class EditorCamera : public HierarchyListener {
    public:
        EditorCamera(Ref<RenderTarget> target);
        void angles(glm::vec3 angles);
        void translateAngles(glm::vec3 angles);
        void focus(glm::vec3 position);
        void update();
        void zoom(float distance);
        float zoom();

        void nodeActive(Ref<Node> &active) override;

        glm::vec3 calculatePosition(glm::vec3 angle, float distance);
        Ref<Camera> camera();
    private:
        void calculateTransform();
        glm::vec3 _focus;
        glm::vec3 _focusTarget;
        float _distance = 0;
        float _distanceTarget = 0;
        glm::vec3 _angles = glm::vec3(0,0,0);
        glm::vec3 _anglesTarget = glm::vec3(0,0,0);
        Ref<Camera> _camera;
    };
}


#endif //CPPMC_EDITORCAMERA_H
