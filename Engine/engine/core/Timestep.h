//
// Created by Gerry on 2020-08-10.
//

#ifndef TIMESTEP_H
#define TIMESTEP_H

namespace VoxEng {
    class Timestep {
    public:
        Timestep(float time = 0.0f) : time(time) {}

        operator float() const {
            return time;
        }

        float getSeconds() {
            return time;
        }

        float getMilli() {
            return time * 1000;
        }

    private:
        float time;
    };
}
#endif //TIMESTEP_H