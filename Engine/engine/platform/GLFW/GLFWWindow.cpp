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

void APIENTRY glDebugHandler(GLenum source, GLenum type, unsigned int id, GLenum severity,
                             GLsizei length, const char *message, const void *userParam);

VoxEng::GLFWWindow::GLFWWindow(const WindowAttributes& attributes) : Window(attributes) {
    char errorCode[1024];
    const char** outError = reinterpret_cast<const char **>(&errorCode);
    if(!glfwInit()) {
        glfwGetError(outError);
        DEBUG_ERROR("Error initializing glfw [%s]\n",errorCode);
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #ifdef DEBUG_ENABLE
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    #endif

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
        DEBUG_ERROR("Failed to init glad!");
        exit(-1);
    }
    glViewport(0,0,width(),height());
    /*
    glEnable(GL_CULL_FACE);
    glCullFace(GL_CCW);

    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);
*/
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

    //Debug output
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugHandler, nullptr);
#endif
    lockMouse(true);

    glEnable(GL_DEPTH_TEST);

    //TODO: abstract out to interface so not bound to opengl.
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);
    //glCullFace(GL_FRONT);
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

void APIENTRY glDebugHandler(GLenum source, GLenum type, unsigned int id, GLenum severity,
                             GLsizei length, const char *message, const void *userParam) {

    if(id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;

    std::cerr << "GL ERROR["<< id <<"] " << std::endl;
    std::cerr << "\t" <<message << std::endl;
    std::cerr << "\tSource: ";
    switch(source) {
        case GL_DEBUG_SOURCE_API: std::cerr << "Api"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: std::cerr << "Window"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Shader"; break;
        case GL_DEBUG_SOURCE_APPLICATION: std::cerr << "Application"; break;
        case GL_DEBUG_SOURCE_OTHER: std::cerr << "Other"; break;
    }
    std::cerr << std::endl;

    std::cerr << "\tType: ";
    switch(type) {
        case GL_DEBUG_TYPE_ERROR: std::cerr << "Error"; break;
        case GL_DEBUG_TYPE_PERFORMANCE: std::cerr << "Performance"; break;
        case GL_DEBUG_TYPE_PORTABILITY: std::cerr << "Portability"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cerr << "Deprecated"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: std::cerr << "Undefined"; break;
        case GL_DEBUG_TYPE_OTHER: std::cerr << "Other"; break;
    }
    std::cerr << std::endl;
    if(severity == GL_DEBUG_SEVERITY_HIGH) {
        exit(id);
    }

}