//
// Created by Gerry on 2021-05-12.
//

#ifndef CPPMC_OPENGLFBO_H
#define CPPMC_OPENGLFBO_H

#include <core/graphics/FBO.h>

namespace Ziti {
    class OpenGLFBO : public FBO {
    public:
        OpenGLFBO(int width, int height, FBOBuffers buffers);

        void bind() override;

        void unbind() override;

        Ref<Texture> getBufferTexture(FBOBuffers buffer) override;

        void clear() override;

        ~OpenGLFBO() override;

    private:
        void genTexture(FBOBuffers buffer, unsigned int type, TextureDetails& details);
        unsigned int _fbo;
    };
}


#endif //CPPMC_OPENGLFBO_H
