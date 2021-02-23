//
// Created by Gerry on 2020-08-12.
//

#ifndef CPPMC_OPENGLTEXTURE_H
#define CPPMC_OPENGLTEXTURE_H

#include <rendering/Texture.h>

namespace VoxEng {
    class OpenGLTexture : public Texture {
    public:

        OpenGLTexture(const TextureDetails& details, int textureId, int x,int y,int width,int height) : Texture(details),textureId(textureId),x(x),y(y),mWidth(width),mHeight(height){}

        void bind() override;

        void bind(int location) override;

        void unbind() override;

        int width() override;

        int height() override;

        ~OpenGLTexture() override;

        Ref<Texture> subTexture(int x, int y, int width, int height) override;

        static Ref<OpenGLTexture> create(const char *path, const TextureDetails &details);
    private:

        static int convert(TextureWrap wrap);
        static int convert(TextureFilter wrap);
        static int convert(TextureType wrap);

        int textureId,x,y,mWidth, mHeight, mtextureType;
    };
}


#endif //CPPMC_OPENGLTEXTURE_H
