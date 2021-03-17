//
// Created by Gerry on 2020-08-10.
//

#ifndef TIMESTEP_H
#define TIMESTEP_H

namespace VoxEng {
    class Timestep {
    public:
        Timestep(float time = 0.0f);
        operator float() const;
        float getSeconds();
        unsigned int getMs();

    private:
        float time;
    };
}
#endif //TIMESTEP_H