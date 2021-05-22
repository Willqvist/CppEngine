//
// Created by Gerry on 2021-05-12.
//

#ifndef CPPMC_FBO_H
#define CPPMC_FBO_H

#include <unordered_map>
#include "Texture.h"

namespace Ziti {

    enum FBOBuffers {
        COLOR = 1,DEPTH = 2,STENCIL = 4, DEPTH_STENCIL = 8
    };

    inline FBOBuffers operator|(FBOBuffers a, FBOBuffers b)
    {
        return static_cast<FBOBuffers>(static_cast<int>(a) | static_cast<int>(b));
    }

    class FBO {
    public:
        FBO(int width, int height, FBOBuffers buffers);
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void clear() = 0;
        virtual Ref<Texture> getBufferTexture(FBOBuffers buffer) = 0;
        bool isBuffer(FBOBuffers buffers);

        static Ref<FBO> create(int width, int height, FBOBuffers buffers);

        virtual ~FBO() = default;
    protected:
        FBOBuffers _buffers;
        std::unordered_map<FBOBuffers, Ref<Texture>> _textures;
        int _width, _height;
    };
}


#endif //CPPMC_FBO_H
