//
// Created by Gerry on 2021-05-20.
//

#ifndef CPPMC_CAMERA3D_H
#define CPPMC_CAMERA3D_H

#include "Node.h"

namespace Ziti {
    class Camera3D : public Node {
        ISCLASS(Camera3D,Node)

        Camera3D();
        Ref<Camera> internal();

        void start() override;

    private:
        Ref<Camera> _camera;
    };
}


#endif //CPPMC_CAMERA3D_H
