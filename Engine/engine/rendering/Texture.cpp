//
// Created by Gerry on 2020-08-12.
//

#include <core/GraphicsLibrary.h>
#include <platform/OpenGL/OpenGLTexture.h>
#include "Texture.h"

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
