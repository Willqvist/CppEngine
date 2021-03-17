//
// Created by Gerry on 2020-08-12.
//

#include <core/GraphicsLibrary.h>
#include <platform/OpenGL/OpenGLTexture.h>
#include "Texture.h"
#include <core/GraphicsLibrary.h>

VoxEng::TextureDetails VoxEng::Texture::defaultDetails = {
        TextureType::T_2D,
        TextureWrap::CLAMP_TO_EDGE,
        TextureFilter::LINEAR,
        TextureFilter::NEAREST
};

VoxEng::Texture::Texture(const VoxEng::TextureDetails &details): mDetails(details) {};

VoxEng::Ref<VoxEng::Texture> VoxEng::Texture::create(const char *path, const VoxEng::TextureDetails &details) {
    switch(GraphicsLibrary::library()) {
        case Library::OPENGL:
            return OpenGLTexture::create(path,details);
            break;
    }
    return nullptr;
}

VoxEng::Ref<VoxEng::Texture> VoxEng::Texture::create(const char *path) {
    switch(GraphicsLibrary::library()) {
        case Library::OPENGL:
            return OpenGLTexture::create(path,defaultDetails);
            break;
    }
    return nullptr;
}

