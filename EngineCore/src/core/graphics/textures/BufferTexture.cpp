//
// Created by Gerry on 2021-05-12.
//

#include "core/graphics/textures/BufferTexture.h"
#include "../platform/opengl/textures/OpenGLBufferTexture.h"

Ziti::BufferTexture::BufferTexture(Ziti::BufferTextureType type, int width, int height) : _type(type), _width(width), _height(height) {

}

Ziti::Ref<Ziti::BufferTexture> Ziti::BufferTexture::create(Ziti::BufferTextureType type, int width, int height) {
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL: return std::shared_ptr<OpenGLBufferTexture>(new OpenGLBufferTexture(type, width, height));
    }
}
