//
// Created by Gerry on 2021-03-15.
//
#include "core/graphics/GraphicsCore.h"

Ziti::GraphicsAPI &Ziti::GraphicsCore::api() {
    return GraphicsCore::_library;
}
