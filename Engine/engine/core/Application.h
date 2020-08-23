//
// Created by Gerry on 2020-08-10.
//

#ifndef CPPMC_APPLICATION_H
#define CPPMC_APPLICATION_H

#include <event/Events.h>
#include "Window.h"
#include "Core.h"
#include "Timestep.h"
#include "Input.h"

namespace VoxEng {

    struct RuntimeData {
        int fps,ups;
        float frameTime;
        std::vector<float> frames;
    };

    class Application: public EventListener {
    public:

        Application(WindowAttributes& attributes);

        virtual void init() = 0;

        void run();

        virtual ~Application();

        void onEvent(Event &ev) override final;

        Ref<Window>& getWindow();
        static Application* getApplication() {
            return application;
        }

        RuntimeData& getRuntimeData() {
            return data;
        }

    protected:
        void update(Timestep& delta);

        void render();

        virtual void renderDebug() {};

        virtual void destroy() = 0;

        virtual void event(Event& ev) = 0;

        RuntimeData data;
        Ref<Window> window;
        bool running = true;
    private:
        bool onWindowCloseEvent(WindowCloseEvent& ev);
        bool onWindowResizeEvent(WindowResizeEvent& ev);
        float prevFrameTime = 0.0f;
        Ref<Input> inputHandler;
        inline static Application* application;
        friend class Scene;
        friend class EntryPoint;
    };
}


#endif //CPPMC_APPLICATION_H
