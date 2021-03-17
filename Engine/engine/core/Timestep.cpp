//
// Created by Gerry on 2021-03-16.
//
#include "Timestep.h"

VoxEng::Timestep::operator float() const {
    return time;
}

float VoxEng::Timestep::getSeconds() {
    return time;
}

unsigned int VoxEng::Timestep::getMs() {
    return static_cast<unsigned int>(time*1000);
}

VoxEng::Timestep::Timestep(float time) : time(time) {}