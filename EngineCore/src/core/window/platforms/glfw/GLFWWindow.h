//
// Created by Gerry on 2020-08-09.
//

#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/rendering/Viewport.h>
#include <core/window/Window.h>

typedef struct GLFWwindow WindowGLFW;
namespace Ziti {
    class GLFWWindow : public Window {
    public:
        GLFWWindow(const WindowAttributes& attributes);

        int width() override;

        int height() override;

        void enableVSync(bool enable) override;

        void update() override;

        void clear() override;

        void lockMouse(bool locked) override;

        ~GLFWWindow() override;

        void bind() override;

        void unbind() override;

        void swap() override;


        WindowGLFW* ptr();


    private:
        int _width, _height;
        bool _vsync;
        std::string _title;
        void setupListeners();

        WindowGLFW* _window;
        
    };
}


#endif //GLFWWINDOW_H
