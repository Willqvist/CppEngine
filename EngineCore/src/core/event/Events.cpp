//
// Created by Gerry on 2021-03-16.
//
#include "core/event/Events.h"

Ziti::KeyPressEvent::KeyPressEvent(int key, Ziti::InputState state): _key(key), _state(state){}

Ziti::MousePressEvent::MousePressEvent(int key, Ziti::InputState state): _key(key), _state(state){}

Ziti::WindowResizeEvent::WindowResizeEvent(int width, int height): _width(width), _height(height){};

