//
// Created by Gerry on 2020-08-10.
//

#ifndef CPPMC_APPLICATION_H
#define CPPMC_APPLICATION_H

#include <event/WindowClose.h>
#include "Window.h"
#include "Core.h"
#include "Timestep.h"

namespace VoxEng {
    class Application: public EventListener {
    public:

        Application(WindowAttributes& attributes);

        virtual void init() = 0;

        void run();

        virtual ~Application();

        void onEvent(Event &ev) override final;

        Ref<Window>& getWindow();

    protected:
        virtual void update(Timestep& delta) = 0;

        virtual void render() = 0;

        virtual void renderDebug() {};

        virtual void destroy() = 0;

        virtual void event(Event& ev) = 0;

        Ref<Window> window;
        bool running = true;
    private:
        bool onWindowCloseEvent(WindowClose& ev);
        float prevFrameTime = 0.0f;
    };
}


#endif //CPPMC_APPLICATION_H
