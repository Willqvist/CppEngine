//
// Created by Gerry on 2020-08-12.
//

#include <core/GraphicsLibrary.h>
#include <platform/OpenGL/OpenGLRenderingCommand.h>
#include "RenderingCommand.h"

void VoxEng::RenderingCommand::clearScreenColor(float red, float green, float blue, float alpha) {
    switch (GraphicsLibrary::library()) {
        case Library::OPENGL:
            OpenGLRenderingCommand::clearScreenColor(red,green,blue,alpha);
            break;
    }
}

void VoxEng::RenderingCommand::clear(VoxEng::BUFFER_BIT bit) {
    switch (GraphicsLibrary::library()) {
        case Library::OPENGL:
            OpenGLRenderingCommand::clear(bit);
            break;
    }
}

void VoxEng::RenderingCommand::viewport(int x, int y, int width, int height) {

}
