//
// Created by Gerry on 2020-08-09.
//
#include "Engine.h"
#include <memory>
#include <core/GraphicsLibrary.h>
#include "core/Core.h"
using namespace VoxEng;
extern VoxEng::Application* entry();

int main(int argc, char** argv) {
    GraphicsLibrary::library() = GRAPHICS_LIBRARY;
    Application* app = entry();
    std::shared_ptr appPtr = std::shared_ptr<Application>(app);
    app->getWindow()->addEventListener(appPtr);
    app->init();
    app->run();
    return 0;
}