//
// Created by Gerry on 2020-08-12.
//

#include <core/graphics/GraphicsCore.h>
#include "core/graphics/GraphicsCommand.h"
#include "platform/opengl/OpenGLRenderingCommand.h"

void Ziti::GraphicsCommand::clearScreenColor(float red, float green, float blue, float alpha) {
    switch (GraphicsCore::api()) {
        case GraphicsAPI::OPENGL:
            OpenGLRenderingCommand::clearScreenColor(red,green,blue,alpha);
            break;
    }
}

void Ziti::GraphicsCommand::clear(Ziti::BUFFER_BIT bit) {
    switch (GraphicsCore::api()) {
        case GraphicsAPI::OPENGL:
            OpenGLRenderingCommand::clear(bit);
            break;
    }
}

void Ziti::GraphicsCommand::viewport(int x, int y, int width, int height) {

}
