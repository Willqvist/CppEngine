//
// Created by Gerry on 2020-08-12.
//

#ifndef CPPMC_OPENGLTEXTURE_H
#define CPPMC_OPENGLTEXTURE_H


#include <core/graphics/Texture.h>

namespace Ziti {
    class OpenGLTexture : public Texture {
    public:
        int depth() override;

        void setDimensions(int width, int height, int depth) override;

        void setPixels(unsigned char *data, Ownership owns) override;

        void upload() override;

        OpenGLTexture(const TextureDetails& details, int textureId, int x,int y,int width,int height);

        void activate() override;

        void activate(int location) override;

        void deactivate() override;

        int width() override;

        int height() override;

        int textureId();

        ~OpenGLTexture() override;

        static Ref<OpenGLTexture> create(const char *path, const TextureDetails &details);
        static Ref<OpenGLTexture> create(const TextureType &type);
        static Ref<OpenGLTexture> create(const TextureDetails &details);
    private:

        static int convert(TextureWrap wrap);
        static int convert(TextureFilter wrap);
        static int convert(TextureType wrap);
        static int convert(TextureFormat format);
        static int convert(TextureDataType type);
        unsigned char* _data = nullptr;
        Ownership  _owns = Ownership::No;
        int _textureId,_x,_y,_width, _height,_depth, _textureType;
    };
}


#endif //CPPMC_OPENGLTEXTURE_H
