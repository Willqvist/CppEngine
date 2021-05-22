//
// Created by Gerry on 2020-08-10.
//

#ifndef CPPMC_EVENTS_H
#define CPPMC_EVENTS_H


#include "Event.h"
namespace Ziti {

    enum class InputState {
        PRESSED, RELEASED, HOLD
    };

    class WindowCloseEvent : public Event {
    public:
        EVENT(WINDOW_CLOSE);
    };

    class KeyPressEvent : public Event {
    public:
        int _key;
        InputState _state;
        KeyPressEvent(int key,InputState state);
        EVENT(KEY_PRESS);
    };

    class MousePressEvent : public Event {
    public:
        int _key;
        InputState _state;
        MousePressEvent(int key,InputState state);
        EVENT(MOUSE_PRESS);
    };

    class MouseMoveEvent : public Event {
    public:
        double _x, _y;
        MouseMoveEvent(double x,double y): _x(x), _y(y){};
        EVENT(MOUSE_MOVE);
    };

    class WindowResizeEvent : public Event {
    public:
        int _width, _height;
        WindowResizeEvent(int width,int height);
        EVENT(WINDOW_RESIZE);
    };
}


#endif //CPPMC_EVENTS_H
