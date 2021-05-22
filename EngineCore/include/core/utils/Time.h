//
// Created by Gerry on 2021-05-07.
//

#ifndef CPPMC_TIME_H
#define CPPMC_TIME_H

#include <chrono>
namespace Ziti {
    class Time {
    public:
        static unsigned int ms() {
            return (unsigned int) std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
        }

        static float seconds() {
            return Time::ms()/1000.0f;
        }

        static float delta() {
            return _delta;
        }
    private:
        static inline float _delta = 0;
        friend class GameEngine;
    };
}
#endif //CPPMC_TIME_H
