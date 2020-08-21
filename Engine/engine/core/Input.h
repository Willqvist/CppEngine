//
// Created by Gerry on 2020-08-20.
//

#ifndef CPPMC_INPUT_H
#define CPPMC_INPUT_H

#include "event/EventListener.h"
#include "KeyCode.h"
#include "MouseCode.h"
#include <core/Logger.h>
#include <event/Events.h>
#include <glm/vec2.hpp>
#include "glm/detail/type_vec2.hpp"
#include <core/Core.h>
namespace VoxEng {
    class Input : public EventListener {
        friend class Application;
    public:
        Input() {}
        static bool isKeyDown(KeyCode key) {
            return keys[static_cast<unsigned int >(key)];
        }
        static bool isMouseDown(Mouse key) {
            return mousePress[static_cast<unsigned int >(key)];
        }
        static glm::vec2 getMouseDelta() {
            return mousePos-prevMousePos;
        }

        static glm::vec2 getMousePosition() {
            return mousePos;
        }
    protected:
        void onEvent(Event &ev) override {
            EventExecutor e(ev);
            e.bind<MouseMoveEvent>(BIND_LAMBDA(onMouseMove));
            e.bind<MousePressEvent>(BIND_LAMBDA(onMousePress));
            e.bind<KeyPressEvent>(BIND_LAMBDA(onKeyPress));
        }
        void poll() {
            prevMousePos = mousePos;
        }
    private:
        inline static bool keys[349];
        inline static bool mousePress[8];
        inline static glm::vec2 prevMousePos = glm::vec2(0,0);
        inline static bool foundMousePos = false;
        inline static glm::vec2 mousePos = glm::vec2(0,0);
        bool onMouseMove(MouseMoveEvent& ev) {
            prevMousePos = mousePos;
            mousePos = glm::vec2(ev.x,ev.y);
            if(!foundMousePos) {
                prevMousePos = mousePos;
                foundMousePos = true;
            }
            return true;
        }

        bool onMousePress(MousePressEvent& ev) {
            mousePress[ev.key] = ev.state == InputState::PRESSED || ev.state == InputState::HOLD ? true : false;
            return true;
        }

        bool onKeyPress(KeyPressEvent& ev) {
            keys[ev.key] = ev.state == InputState::PRESSED || ev.state == InputState::HOLD ? true : false;
            return true;
        }
    };

}
#endif //CPPMC_INPUT_H
