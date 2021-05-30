//
// Created by Gerry on 2021-03-15.
//
#include "core/window/Input.h"
#include <core/event/Events.h>
#include "glm/detail/type_vec2.hpp"
#include <core/event/Events.h>
#include <core/Memory.h>

bool Ziti::Input::isKeyDown(Ziti::KeyCode key) {
    return keys[static_cast<unsigned int >(key)];
}

bool Ziti::Input::isMouseDown(Ziti::MouseCode key) {
    return mousePress[static_cast<unsigned int >(key)];
}

glm::vec2 Ziti::Input::getMouseDelta() {
    return mousePos-prevMousePos;
}

glm::vec2 Ziti::Input::getMousePosition() {
    return mousePos;
}

void Ziti::Input::onEvent(Ziti::Event &ev) {
    EventExecutor e(ev);
    e.bind<MouseMoveEvent>(LAMBDA(onMouseMove));
    e.bind<MousePressEvent>(LAMBDA(onMousePress));
    e.bind<KeyPressEvent>(LAMBDA(onKeyPress));
    e.bind<MouseWheelEvent>(LAMBDA(onMouseWheelMove));
}

void Ziti::Input::poll() {
    prevMousePos = mousePos;
    _scrollSpeed = 0;
}

bool Ziti::Input::onMouseMove(Ziti::MouseMoveEvent &ev) {
    prevMousePos = mousePos;
    mousePos = glm::vec2(ev._x,ev._y);
    if(!foundMousePos) {
        prevMousePos = mousePos;
        foundMousePos = true;
    }
    return true;
}

bool Ziti::Input::onMousePress(Ziti::MousePressEvent &ev) {
    mousePress[ev._key] = ev._state == InputState::PRESSED || ev._state == InputState::HOLD ? true : false;
    return true;
}

bool Ziti::Input::onKeyPress(Ziti::KeyPressEvent &ev) {
    keys[ev._key] = ev._state == InputState::PRESSED || ev._state == InputState::HOLD ? true : false;
    return true;
}

bool Ziti::Input::onMouseWheelMove(Ziti::MouseWheelEvent &ev) {
    printf("scroll speed: %f\n",ev._amount);
    _scrollSpeed = ev._amount;
    return true;
}

bool Ziti::Input::keys[KEY_SIZE];
bool Ziti::Input::mousePress[MOUSE_SIZE];
bool Ziti::Input::foundMousePos;
float Ziti::Input::_scrollSpeed = 0;
float Ziti::Input::prevScrollSpeed = 0;

float Ziti::Input::scrollSpeed() {
    return _scrollSpeed;
}

glm::vec2 Ziti::Input::prevMousePos;
glm::vec2 Ziti::Input::mousePos;
