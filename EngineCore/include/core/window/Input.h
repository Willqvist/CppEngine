//
// Created by Gerry on 2020-08-20.
//

#ifndef CPPMC_INPUT_H
#define CPPMC_INPUT_H

#include "core/event/EventListener.h"
#include <glm/vec2.hpp>
#define KEY_SIZE 349
#define MOUSE_SIZE 8
namespace Ziti {

    class MouseMoveEvent;
    class MouseWheelEvent;
    class MousePressEvent;
    class KeyPressEvent;
    enum class KeyCode : unsigned int;
    enum class MouseCode : unsigned int;

    class Input : public EventListener {
        friend class Application;
    public:
        Input() {}
        static bool isKeyDown(KeyCode key);
        static bool isMouseDown(MouseCode key);
        static float scrollSpeed();
        static glm::vec2 getMouseDelta();
        static glm::vec2 getMousePosition();
        void poll();
    protected:
        void onEvent(Event &ev) override;
    private:
        static bool keys[KEY_SIZE];
        static bool mousePress[MOUSE_SIZE];
        static glm::vec2 prevMousePos;
        static float prevScrollSpeed;
        static float _scrollSpeed;
        static bool foundMousePos;
        static glm::vec2 mousePos;

        bool onMouseMove(MouseMoveEvent& ev);

        bool onMouseWheelMove(MouseWheelEvent& ev);

        bool onMousePress(MousePressEvent& ev);

        bool onKeyPress(KeyPressEvent& ev);
    };

}
#endif //CPPMC_INPUT_H
