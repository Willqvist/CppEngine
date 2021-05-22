//
// Created by Gerry on 2020-08-09.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <core/rendering/Viewport.h>
#include <core/Memory.h>
#include <string>
#include <core/rendering/RenderTarget.h>

namespace Ziti {

    class EventListener;
    class Event;

    struct WindowAttributes {
        int width = 1080;
        int height = 1920;
        std::string title = "Ziti Application";
        bool vsync = true;
    };

    class Window : public RenderTarget {
    public:

        void addEventListener(const Ref<EventListener>& listener);

        void sendEvent(Event& ev);

        virtual int width() = 0;

        virtual int height() = 0;

        virtual void enableVSync(bool enable) = 0;

        virtual void update() = 0;

        virtual void clear() = 0;

        virtual void swap() = 0;

        virtual void lockMouse(bool locked) = 0;

        virtual ~Window() = default;

        static Ref<Window> createWindow(const WindowAttributes& attributes);

    protected:

        std::vector<Ref<EventListener>> _listeners;
    };
}

#endif //WINDOW_H
