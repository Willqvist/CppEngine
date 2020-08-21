//
// Created by Gerry on 2020-08-09.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <event/EventListener.h>
#include <vector>
#include "Core.h"

namespace VoxEng {
    struct WindowAttributes {
        int width;
        int height;
        char *title;
        bool vsync;
    };

    class Window {
    public:

        void addEventListener(const Ref<EventListener>& listener) {
            listeners.push_back(listener);
        }

        void sendEvent(Event& ev) {
            for(Ref<EventListener>& listener : listeners) {
                listener->onEvent(ev);
            }
        }

        virtual int width() = 0;

        virtual int height() = 0;

        virtual void enableVSync(bool enable) = 0;

        virtual void update() = 0;

        virtual void clear() = 0;

        virtual void lockMouse(bool locked) = 0;

        virtual ~Window() = default;

        static Ref<Window> createWindow(const WindowAttributes& attributes);

    protected:
        Window(WindowAttributes const &attributes) : mWidth(attributes.width), mHeight(attributes.height),
                                                     mTitle(attributes.title), mVsync(attributes.vsync) {}

        int mWidth, mHeight;
        bool mVsync;
        char *mTitle;
        std::vector<Ref<EventListener>> listeners;
    };
}

#endif //WINDOW_H
