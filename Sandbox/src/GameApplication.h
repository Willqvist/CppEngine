//
// Created by Gerry on 2020-08-10.
//

#ifndef CPPMC_GAMEAPPLICATION_H
#define CPPMC_GAMEAPPLICATION_H


#include <core/Application.h>
using namespace VoxEng;
class GameApplication: public Application {
public:
protected:
    void event(Event &ev) override;

public:

    GameApplication(WindowAttributes &attributes);

    void init() override;

    void update(Timestep& delta) override;

    void render() override;

    void destroy() override;

    ~GameApplication() override;
};


#endif //CPPMC_GAMEAPPLICATION_H
