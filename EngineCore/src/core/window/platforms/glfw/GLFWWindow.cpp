//
// Created by Gerry on 2020-08-09.
//
#include <core/event/Events.h>
#include <core/Memory.h>
#include <core/graphics/GraphicsCommand.h>
#include "GLFWWindow.h"
#include "iostream"

void APIENTRY glDebugHandler(GLenum source, GLenum type, unsigned int id, GLenum severity,
                             GLsizei length, const char *message, const void *userParam);

Ziti::GLFWWindow::GLFWWindow(const WindowAttributes& attributes) : _width(attributes.width), _height(attributes.height),
                                                                   _title(attributes.title), _vsync(attributes.vsync) {
    char errorCode[1024];
    setViewport(_width,_height);
    const char** outError = reinterpret_cast<const char **>(&errorCode);
    if(!glfwInit()) {
        glfwGetError(outError);
        printf("Error initializing glfw [%s]\n",errorCode);
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #ifdef DEBUG_ENABLE
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    #endif

    _window = glfwCreateWindow(_width,_height,_title.c_str(),NULL,NULL);
    printf("HERE!\n");
    if(!_window) {
        glfwTerminate();
        glfwGetError(outError);
        printf("Error creating window pointer [%s]\n",errorCode);
        exit(1);
    }

    glfwSetWindowUserPointer(_window, reinterpret_cast<void*>(this));
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(attributes.vsync);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); //TODO: move out
    if(!status)
    {
        printf("Failed to init glad!");
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
    /*
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
     */
    lockMouse(false);

    glEnable(GL_DEPTH_TEST);

    //TODO: abstract out to interface so not bound to opengl.
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);
    //glCullFace(GL_FRONT);
}


int Ziti::GLFWWindow::width() {
    return _width;
}

int Ziti::GLFWWindow::height() {
    return _height;
}

void Ziti::GLFWWindow::enableVSync(bool enable) {
    this->_vsync = enable;
}

void Ziti::GLFWWindow::update() {
    if(glfwWindowShouldClose(_window)) {
        WindowCloseEvent closeEvent;
        sendEvent(closeEvent);
    }
    glfwPollEvents();
    /*
#ifdef DEBUG_ENABLE
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
#endif
     */
}

void Ziti::GLFWWindow::clear() {
    /*
#ifdef DEBUG_ENABLE
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
     */
    //RenderingCommand::clearScreenColor(1,0,0,1);
    //glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    //glfwSwapBuffers(_window);
    //GraphicsCommand::clearScreenColor(0,0,0,1);
    //GraphicsCommand::clear(BUFFER_BIT::COLOR | BUFFER_BIT::DEPTH);
}

Ziti::GLFWWindow::~GLFWWindow() {
    glfwTerminate();
}

void Ziti::GLFWWindow::setupListeners() {
    glfwSetKeyCallback(_window,[](GLFWwindow* window, int key, int scancode, int action, int mode){
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

    glfwSetMouseButtonCallback(_window,[](GLFWwindow* window, int button, int action, int mods){
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

    glfwSetCursorPosCallback(_window,[](GLFWwindow* window, double x,double y){
        GLFWWindow* windowPointer = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        MouseMoveEvent ev(x,y);
        windowPointer->sendEvent(ev);
    });

    glfwSetWindowSizeCallback(_window,[](GLFWwindow* window, int width,int height){
        glViewport(0,0,width,height);
        GLFWWindow* windowPointer = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        windowPointer->_width = width;
        windowPointer->_height = height;
        windowPointer->setViewport(width,height);
        WindowResizeEvent ev(width,height);
        windowPointer->sendEvent(ev);
    });

    glfwSetScrollCallback(_window,[](GLFWwindow* window, double xOffset,double yOffset){
        MouseWheelEvent ev(yOffset);
        GLFWWindow* windowPointer = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        windowPointer->sendEvent(ev);
    });

    WindowResizeEvent ev(_width,_height);
    this->sendEvent(ev);
}

void Ziti::GLFWWindow::lockMouse(bool locked) {
    if(locked) {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (glfwRawMouseMotionSupported())
            glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    } else {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPos(_window,_width/2,_height/2);
    }
}

void Ziti::GLFWWindow::bind() {
    //TODO: if in editor... bind to view image!!.
    glViewport(0,0,width(),height());
}

void Ziti::GLFWWindow::unbind() {

}

WindowGLFW *Ziti::GLFWWindow::ptr() {
    return _window;
}

void Ziti::GLFWWindow::swap() {
    glfwSwapBuffers(_window);
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