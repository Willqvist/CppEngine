//
// Created by Gerry on 2020-08-09.
//

#include "core/window/Window.h"
#include "platforms/glfw/GLFWWindow.h"
#include <core/Memory.h>
#include <core/event/EventListener.h>

Ziti::Ref<Ziti::Window> Ziti::Window::createWindow(const WindowAttributes& attributes) {
    return CreateRef<Ziti::GLFWWindow>(std::move(attributes));
}

void Ziti::Window::sendEvent(Ziti::Event &ev) {
    for(Ref<EventListener>& listener : _listeners) {
        listener->onEvent(ev);
    }
}

void Ziti::Window::addEventListener(const Ziti::Ref<Ziti::EventListener> &listener) {
    _listeners.push_back(listener);
}
