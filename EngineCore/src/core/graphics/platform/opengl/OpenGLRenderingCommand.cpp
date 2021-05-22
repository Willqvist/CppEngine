//
// Created by Gerry on 2020-08-12.
//

#include <glad/glad.h>
#include "OpenGLRenderingCommand.h"

void Ziti::OpenGLRenderingCommand::clearScreenColor(float red, float green, float blue, float alpha) {
    glClearColor(red,green,blue,alpha);
}

void Ziti::OpenGLRenderingCommand::clear(Ziti::BUFFER_BIT bit) {
   glClear(static_cast<GLbitfield>(bit));
}

void Ziti::OpenGLRenderingCommand::viewport(int x, int y, int width, int height) {
    glViewport(x,y,width,height);
}
