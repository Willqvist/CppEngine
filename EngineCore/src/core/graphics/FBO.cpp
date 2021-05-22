//
// Created by Gerry on 2021-05-12.
//

#include "core/graphics/FBO.h"
#include "platform/opengl/OpenGLFBO.h"

Ziti::FBO::FBO(int width, int height, Ziti::FBOBuffers buffers) : _buffers(buffers), _width(width), _height(height) {

}

bool Ziti::FBO::isBuffer(Ziti::FBOBuffers buffers) {
    return (buffers & _buffers) > 0;
}

Ziti::Ref<Ziti::FBO> Ziti::FBO::create(int width, int height, Ziti::FBOBuffers buffers) {
    printf("AM HERE! 5\n");
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL: return CreateRef<OpenGLFBO>(width,height,buffers);
    }
}
