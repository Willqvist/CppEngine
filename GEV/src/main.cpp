//
// Created by Gerry on 2021-05-06.
//

#include <stdio.h>
#include <core/Memory.h>
#include <core/graphics/Texture.h>
#include <core/GameEngine.h>
#include <ZitiView.h>
#include "TestViewApp.h"

using namespace Ziti;
int main() {
    Scope<Application> testapp = CreateScope<TestViewApp>();
    Scope<Application> app = CreateScope<ZitiView::ZitiView>(testapp);
    Scope<GameEngine> engine = CreateScope<GameEngine>(app);
    engine->start();
    return 0;
}
