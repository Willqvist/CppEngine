//
// Created by Gerry on 2020-08-09.
//

#include "Window.h"
#include "platform/GLFW/GLFWWindow.h"


VoxEng::Ref<VoxEng::Window> VoxEng::Window::createWindow(const WindowAttributes& attributes) {
    return CreateRef<VoxEng::GLFWWindow>(std::move(attributes));
}