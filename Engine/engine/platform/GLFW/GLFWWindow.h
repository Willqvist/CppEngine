//
// Created by Gerry on 2020-08-09.
//

#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H
#include <glad/glad.h>
#include "core/Window.h"
#include <GLFW/glfw3.h>
typedef struct GLFWwindow WindowGLFW;
namespace VoxEng {
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

    private:

        void setupListeners();

        WindowGLFW* window;
    };
}


#endif //GLFWWINDOW_H
