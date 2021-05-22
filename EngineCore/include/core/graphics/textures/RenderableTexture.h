//
// Created by Gerry on 2021-05-12.
//

#ifndef ENGINECORE_RENDERABLETEXTURE_H
#define ENGINECORE_RENDERABLETEXTURE_H

#include <core/graphics/Texture.h>
#include <core/rendering/Viewport.h>
#include <core/rendering/RenderTarget.h>
#include <core/graphics/FBO.h>

namespace Ziti {
    class RenderableTexture : public Texture, public RenderTarget {
    public:

        RenderableTexture(FBOBuffers buffers, int width,int height);

        void activate() override;

        void activate(int location) override;

        void bind() override;

        void unbind() override;

        void deactivate() override;

        int width() override;

        int height() override;

        int depth() override;

        void clear();

        Ref<Texture> getBufferTexture(FBOBuffers buffers);

        void setDimensions(int width, int height, int depth) override;

        void setPixels(unsigned char *data, Ownership owns) override;

        void upload() override;
    protected:
        Ref<FBO> _fbo;
    };
}


#endif //ENGINECORE_RENDERABLETEXTURE_H
