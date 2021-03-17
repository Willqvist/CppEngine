//
// Created by Gerry on 2020-08-21.
//

#ifndef CPPMC_CAMERAMOVEMENT_H
#define CPPMC_CAMERAMOVEMENT_H

#include <scene/components/VoxComponent.h>
using namespace VoxEng;
class CameraMovement: public VoxComponent {
public:
    void update(VoxEng::Timestep ts) override;
private:
    float movementSpeed = 14.2f;
    float rotationSpeed = 30.2f;

};
#endif //CPPMC_CAMERAMOVEMENT_H
