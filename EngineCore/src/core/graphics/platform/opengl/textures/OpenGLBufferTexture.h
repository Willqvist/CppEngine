//
// Created by Gerry on 2021-05-12.
//

#ifndef ENGINECORE_OPENGLBUFFERTEXTURE_H
#define ENGINECORE_OPENGLBUFFERTEXTURE_H

#include <core/graphics/textures/BufferTexture.h>

namespace Ziti {
    class OpenGLBufferTexture : public BufferTexture {
    public:
        OpenGLBufferTexture(BufferTextureType type, int width, int height);

        void activate() override;

        void activate(int location) override;

        void deactivate() override;

        int width() override;

        int height() override;

        int depth() override;

        void setDimensions(int width, int height, int depth) override;

        void setPixels(unsigned char *data, Ownership owns) override;

        void upload() override;
    private:
        unsigned int _rbo;
    };
}


#endif //ENGINECORE_OPENGLBUFFERTEXTURE_H
