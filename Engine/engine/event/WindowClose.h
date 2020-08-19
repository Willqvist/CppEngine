//
// Created by Gerry on 2020-08-10.
//

#ifndef CPPMC_WINDOWCLOSE_H
#define CPPMC_WINDOWCLOSE_H


#include "Event.h"
namespace VoxEng {
    class WindowClose : public Event {
    public:
        EVENT(WINDOW_CLOSE)
    };
}


#endif //CPPMC_WINDOWCLOSE_H
