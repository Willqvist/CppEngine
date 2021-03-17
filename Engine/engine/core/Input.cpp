//
// Created by Gerry on 2021-03-15.
//
#include "Input.h"
#include <event/Events.h>
#include <core/Logger.h>
#include "glm/detail/type_vec2.hpp"
#include <core/Core.h>
#include "KeyCode.h"
#include "MouseCode.h"

bool VoxEng::Input::isKeyDown(VoxEng::KeyCode key) {
    return keys[static_cast<unsigned int >(key)];
}

bool VoxEng::Input::isMouseDown(VoxEng::MouseCode key) {
    return mousePress[static_cast<unsigned int >(key)];
}

glm::vec2 VoxEng::Input::getMouseDelta() {
    return mousePos-prevMousePos;
}

glm::vec2 VoxEng::Input::getMousePosition() {
    return mousePos;
}

void VoxEng::Input::onEvent(VoxEng::Event &ev) {
    EventExecutor e(ev);
    e.bind<MouseMoveEvent>(BIND_LAMBDA(onMouseMove));
    e.bind<MousePressEvent>(BIND_LAMBDA(onMousePress));
    e.bind<KeyPressEvent>(BIND_LAMBDA(onKeyPress));
}

void VoxEng::Input::poll() {
    prevMousePos = mousePos;
}

bool VoxEng::Input::onMouseMove(VoxEng::MouseMoveEvent &ev) {
    prevMousePos = mousePos;
    mousePos = glm::vec2(ev.x,ev.y);
    if(!foundMousePos) {
        prevMousePos = mousePos;
        foundMousePos = true;
    }
    return true;
}

bool VoxEng::Input::onMousePress(VoxEng::MousePressEvent &ev) {
    mousePress[ev.key] = ev.state == InputState::PRESSED || ev.state == InputState::HOLD ? true : false;
    return true;
}

bool VoxEng::Input::onKeyPress(VoxEng::KeyPressEvent &ev) {
    keys[ev.key] = ev.state == InputState::PRESSED || ev.state == InputState::HOLD ? true : false;
    return true;
}

bool VoxEng::Input::keys[KEY_SIZE];
bool VoxEng::Input::mousePress[MOUSE_SIZE];
bool VoxEng::Input::foundMousePos;
glm::vec2 VoxEng::Input::prevMousePos;
glm::vec2 VoxEng::Input::mousePos;
