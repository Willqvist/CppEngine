#include <iostream>
#include <core/Window.h>
#include "Engine.h"
#include "GameApplication.h"

VoxEng::Application* entry() {
    VoxEng::WindowAttributes attributes {
        1080,
        720,
        "Title"
    };

    return new GameApplication(attributes);
}
