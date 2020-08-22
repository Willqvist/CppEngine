//
// Created by Gerry on 2020-08-09.
//
#include <core/Logger.h>
#include <event/Events.h>
#include <rendering/RenderingCommand.h>
#include <core/Input.h>
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
    DEBUG_LOG("ENABLED MOTION %d", glfwRawMouseMotionSupported());

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
    setupListeners();
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
    lockMouse(true);
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
        WindowCloseEvent closeEvent;
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

void VoxEng::GLFWWindow::setupListeners() {
    glfwSetKeyCallback(window,[](GLFWwindow* window, int key, int scancode, int action, int mode){
        GLFWWindow* windowPointer = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        InputState state;
        switch(action) {
            case GLFW_PRESS: state = InputState::PRESSED; break;
            case GLFW_RELEASE: state = InputState::RELEASED; break;
            case GLFW_REPEAT: state = InputState::HOLD; break;
        }
        KeyPressEvent ev(key,state);
        windowPointer->sendEvent(ev);
    });

    glfwSetMouseButtonCallback(window,[](GLFWwindow* window, int button, int action, int mods){
        GLFWWindow* windowPointer = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        InputState state;
        switch(action) {
            case GLFW_PRESS: state = InputState::PRESSED; break;
            case GLFW_RELEASE: state = InputState::RELEASED; break;
            case GLFW_REPEAT: state = InputState::HOLD; break;
        }
        MousePressEvent ev(button,state);
        windowPointer->sendEvent(ev);
    });

    glfwSetCursorPosCallback(window,[](GLFWwindow* window, double x,double y){
        GLFWWindow* windowPointer = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        MouseMoveEvent ev(x,y);
        windowPointer->sendEvent(ev);
    });

    glfwSetWindowSizeCallback(window,[](GLFWwindow* window, int width,int height){
        glViewport(0,0,width,height);
        GLFWWindow* windowPointer = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        windowPointer->mWidth = width;
        windowPointer->mHeight = height;
        WindowResizeEvent ev(width,height);
        windowPointer->sendEvent(ev);
    });
    WindowResizeEvent ev(mWidth,mHeight);
    this->sendEvent(ev);
}

void VoxEng::GLFWWindow::lockMouse(bool locked) {
    if(locked) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (glfwRawMouseMotionSupported())
            glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPos(window,mWidth/2,mHeight/2);
    }
}
