//
// Created by Gerry on 2020-08-09.
//

#include "Window.h"
#include "platform/GLFW/GLFWWindow.h"
#include <event/EventListener.h>


VoxEng::Ref<VoxEng::Window> VoxEng::Window::createWindow(const WindowAttributes& attributes) {
    return CreateRef<VoxEng::GLFWWindow>(std::move(attributes));
}

void VoxEng::Window::sendEvent(VoxEng::Event &ev) {
    for(Ref<EventListener>& listener : listeners) {
        listener->onEvent(ev);
    }
}

void VoxEng::Window::addEventListener(const VoxEng::Ref<VoxEng::EventListener> &listener) {
    listeners.push_back(listener);
}

VoxEng::Window::Window(const VoxEng::WindowAttributes &attributes) : mWidth(attributes.width), mHeight(attributes.height),
mTitle(attributes.title), mVsync(attributes.vsync) {}
