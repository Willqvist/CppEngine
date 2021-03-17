//
// Created by Gerry on 2020-08-20.
//

#ifndef CPPMC_INPUT_H
#define CPPMC_INPUT_H

#include "event/EventListener.h"
#include <glm/vec2.hpp>
#define KEY_SIZE 349
#define MOUSE_SIZE 8
namespace VoxEng {

    class MouseMoveEvent;
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
        static glm::vec2 getMouseDelta();
        static glm::vec2 getMousePosition();
    protected:
        void onEvent(Event &ev) override;
        void poll();
    private:
        static bool keys[KEY_SIZE];
        static bool mousePress[MOUSE_SIZE];
        static glm::vec2 prevMousePos;
        static bool foundMousePos;
        static glm::vec2 mousePos;

        bool onMouseMove(MouseMoveEvent& ev);

        bool onMousePress(MousePressEvent& ev);

        bool onKeyPress(KeyPressEvent& ev);
    };

}
#endif //CPPMC_INPUT_H
