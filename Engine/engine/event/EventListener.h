//
// Created by Gerry on 2020-08-10.
//

#ifndef CPPMC_EVENTLISTENER_H
#define CPPMC_EVENTLISTENER_H

#include "Event.h"
namespace VoxEng {
    class EventListener {
    public:
        virtual void onEvent(Event &ev) = 0;
    };
}

#endif //CPPMC_EVENTLISTENER_H
