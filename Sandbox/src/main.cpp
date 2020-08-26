#include <iostream>
#include <core/Window.h>
#include "Engine.h"
#include "GameApplication.h"

VoxEng::Application* entry() {
    VoxEng::WindowAttributes attributes {
        2160,
        1000,
        "Title"
    };
    return new GameApplication(attributes);
}
