//
// Created by Gerry on 2020-08-23.
//

#ifndef CPPMC_DEBUGLAYER_H
#define CPPMC_DEBUGLAYER_H

#include <scene/Layer.h>

using namespace VoxEng;
namespace VoxEng {
    class Application;
}
class DebugLayer: public Layer {
public:
    void onCreate() override;
    void render() override;
private:
    Application* app;
};


#endif //CPPMC_DEBUGLAYER_H
