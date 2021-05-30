//
// Created by Gerry on 2021-05-20.
//

#ifndef CPPMC_CAMERA3D_H
#define CPPMC_CAMERA3D_H

#include "Node.h"
#include "Spatial.h"

namespace Ziti {
    class Camera3D : public Spatial {
        ISCLASS(Camera3D,Spatial)

        Camera3D();
        Ref<Camera> internal();

        void start() override;

        void update() override;

        void onPositionChange() override;

        void attributes(Attributes &attributes) override;

    private:
        Ref<Camera> _camera;
    };
}


#endif //CPPMC_CAMERA3D_H
