//
// Created by Gerry on 2020-08-09.
//
#include <core/Logger.h>
#include <event/WindowClose.h>
#include <rendering/RenderingCommand.h>
#include "GLFWWindow.h"
#include "iostream"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
VoxEng::GLFWWindow::GLFWWindow(const WindowAttributes& attributes) : Window(attributes) {
    char errorCode[1024];
    const char** outError = reinterpret_cast<const char **>(&errorCode);
    if(!glfwInit()) {
        glfwGetError(outError);
        DEBUG_ERROR("Error initializing glfw [%s]\n",errorCode);
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(mWidth,mHeight,mTitle,NULL,NULL);
    if(!window) {
        glfwTerminate();
        glfwGetError(outError);
        DEBUG_ERROR("Error creating window pointer [%s]\n",errorCode);
        exit(1);
    }

    glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));
    glfwMakeContextCurrent(window);
    glfwSwapInterval(attributes.vsync);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); //TODO: move out
    if(!status)
    {
        DEBUG_ERROR("Faild to init glad!");
        exit(-1);
    }
    glViewport(0,0,width(),height());
#ifdef DEBUG_ENABLE
    //IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");
#endif
}


int VoxEng::GLFWWindow::width() {
    return mWidth;
}

int VoxEng::GLFWWindow::height() {
    return mHeight;
}

void VoxEng::GLFWWindow::enableVSync(bool enable) {
    this->mVsync = enable;
}

void VoxEng::GLFWWindow::update() {
    if(glfwWindowShouldClose(window)) {
        WindowClose closeEvent;
        sendEvent(closeEvent);
    }

    glfwPollEvents();
#ifdef DEBUG_ENABLE
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
#endif
}

void VoxEng::GLFWWindow::clear() {
#ifdef DEBUG_ENABLE
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
    //RenderingCommand::clearScreenColor(1,0,0,1);
    //glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glfwSwapBuffers(window);
    RenderingCommand::clearScreenColor(0.3f, 0.8f, 1.0f, 1.0f);
    RenderingCommand::clear(BUFFER_BIT::COLOR | BUFFER_BIT::DEPTH);
}

VoxEng::GLFWWindow::~GLFWWindow() {
    glfwTerminate();
}