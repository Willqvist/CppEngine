//
// Created by Gerry on 2020-08-10.
//

#ifndef CPPMC_EVENT_H
#define CPPMC_EVENT_H
#define EVENT(type) static EVENT_TYPE getStaticType(){return EVENT_TYPE::type;}\
EVENT_TYPE getType(){return EVENT_TYPE::type;}
namespace VoxEng {
    enum class EVENT_TYPE{
        WINDOW_CLOSE=0, KEY_PRESS, MOUSE_MOVE, MOUSE_PRESS,WINDOW_RESIZE
    };
    class Event {
    public:
        virtual EVENT_TYPE getType() = 0;
    private:
        bool handled = false;

        friend class EventExecutor;
    };

    class EventExecutor {
    public:
        EventExecutor(Event& e) : e(e){}

        template<typename T, typename F>
        bool bind(const F &clb)  {
            if (e.getType() == T::getStaticType()) {
                e.handled = clb(static_cast<T&>(e));
                return true;
            }
            return false;
        }

    private:
        Event& e;
    };

}

#endif //CPPMC_EVENT_H
