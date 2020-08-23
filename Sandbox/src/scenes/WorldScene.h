//
// Created by Gerry on 2020-08-23.
//

#ifndef CPPMC_WORLDSCENE_H
#define CPPMC_WORLDSCENE_H

#include <scene/Scene.h>

using namespace VoxEng;
class WorldScene: public Scene {

public:
    void onSceneStart(void *data) override;

};


#endif //CPPMC_WORLDSCENE_H
