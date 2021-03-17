//
// Created by Gerry on 2021-03-16.
//
#include "Events.h"

VoxEng::KeyPressEvent::KeyPressEvent(int key, VoxEng::InputState state): key(key), state(state){}

VoxEng::MousePressEvent::MousePressEvent(int key, VoxEng::InputState state): key(key), state(state){}

VoxEng::WindowResizeEvent::WindowResizeEvent(int width, int height): width(width), height(height){};

