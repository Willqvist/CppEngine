//
// Created by Gerry on 2020-08-10.
//

#ifndef CPPMC_EVENTS_H
#define CPPMC_EVENTS_H


#include "Event.h"
namespace VoxEng {

    enum class InputState {
        PRESSED, RELEASED, HOLD
    };

    class WindowCloseEvent : public Event {
    public:
        EVENT(WINDOW_CLOSE);
    };

    class KeyPressEvent : public Event {
    public:
        int key;
        InputState state;
        KeyPressEvent(int key,InputState state);
        EVENT(KEY_PRESS);
    };

    class MousePressEvent : public Event {
    public:
        int key;
        InputState state;
        MousePressEvent(int key,InputState state);
        EVENT(MOUSE_PRESS);
    };

    class MouseMoveEvent : public Event {
    public:
        double x, y;
        MouseMoveEvent(double x,double y): x(x), y(y){};
        EVENT(MOUSE_MOVE);
    };

    class WindowResizeEvent : public Event {
    public:
        int width, height;
        WindowResizeEvent(int width,int height);
        EVENT(WINDOW_RESIZE);
    };
}


#endif //CPPMC_EVENTS_H
