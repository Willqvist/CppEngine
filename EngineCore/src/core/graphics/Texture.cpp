//
// Created by Gerry on 2020-08-12.
//

#include <core/graphics/GraphicsCore.h>
#include <core/Memory.h>
#include "core/graphics/Texture.h"
#include "platform/OpenGL/OpenGLTexture.h"

Ziti::TextureDetails Ziti::Texture::defaultDetails = {
        TextureType::T_2D,
        TextureWrap::CLAMP_TO_EDGE,
        TextureFilter::LINEAR,
        TextureFilter::NEAREST
};

Ziti::Texture::Texture(const Ziti::TextureDetails &details): _details(details) {};
Ziti::Texture::Texture() : _details(defaultDetails) {

}

Ziti::Ref<Ziti::Texture> Ziti::Texture::create(const std::string &path, const Ziti::TextureDetails &details) {
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL:
            return OpenGLTexture::create(path.c_str(),details);
            break;
    }
    return nullptr;
}


Ziti::Ref<Ziti::Texture> Ziti::Texture::create(const std::string& path) {
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL:
            return OpenGLTexture::create(path.c_str(),defaultDetails);
            break;
    }
    return nullptr;
}

Ziti::Ref<Ziti::Texture> Ziti::Texture::create(const Ziti::TextureType &type) {
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL:
            return OpenGLTexture::create(type);
            break;
    }
    return nullptr;
}

Ziti::Ref<Ziti::Texture> Ziti::Texture::create(const Ziti::TextureDetails &details) {
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL:
            return OpenGLTexture::create(details);
            break;
    }
    return nullptr;
}



