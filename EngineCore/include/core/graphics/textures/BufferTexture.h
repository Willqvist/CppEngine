//
// Created by Gerry on 2021-05-12.
//

#ifndef ENGINECORE_BUFFERTEXTURE_H
#define ENGINECORE_BUFFERTEXTURE_H

#include <core/graphics/Texture.h>

namespace Ziti {

    enum class BufferTextureType {
        DEPTH4_STENCIL8
    };

    class BufferTexture : public Texture {
    public:
        BufferTexture(BufferTextureType type, int width, int height);
        Ref<BufferTexture> create(BufferTextureType type, int width, int height);
    protected:
        int _width, _height;
        BufferTextureType  _type;
    };
}


#endif //ENGINECORE_BUFFERTEXTURE_H
