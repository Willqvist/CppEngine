//
// Created by Gerry on 2020-08-12.
//

#ifndef CPPMC_TEXTURE_H
#define CPPMC_TEXTURE_H

#include <core/graphics/GraphicsCore.h>
#include <core/Memory.h>
#include <string>

namespace Ziti {

    enum class TextureType {
        T_2D,
        T_3D,
        T_CUBE
    };

    enum class TextureWrap {
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER
    };

    enum class TextureFilter {
        LINEAR,
        NEAREST,
    };

    enum class TextureFormat {
        RED = 0, RGB = 1, RGBA = 2, DEPTH_COMPONENT, DEPTH_STENCIL,DEPTH24_STENCIL8
    };

    enum class TextureDataType {
        UBYTE,FLOAT, UINT24_8, UINT
    };

    struct TextureDetails {
        TextureType type = TextureType::T_2D;
        TextureWrap wrapping = TextureWrap::REPEAT;
        TextureFilter min = TextureFilter::NEAREST,max = TextureFilter::NEAREST;
        TextureDataType datatype = TextureDataType::UBYTE;
        TextureFormat format = TextureFormat::RGBA;
        TextureFormat internalFormat = TextureFormat::RGBA;
    };

    class Texture {
    public:
        Texture(const TextureDetails& details);
        Texture();

        virtual void activate() = 0;
        virtual void activate(int location) = 0;
        virtual void deactivate() = 0;

        virtual int width() = 0;
        virtual int height() = 0;
        virtual int depth() = 0;
        virtual void setDimensions(int width,int height, int depth = 0) = 0;
        virtual void setPixels(unsigned char *data, Ownership owns) = 0;
        virtual void upload() = 0;

        virtual ~Texture() = default;

        TextureDetails& details() {
            return _details;
        }

        static Ref<Texture> create(const TextureType& type);
        static Ref<Texture> create(const TextureDetails& details);
        static Ref<Texture> create(const std::string& path, const TextureDetails& type);
        static Ref<Texture> create(const std::string& path);
    protected:
        TextureDetails _details;
        inline static unsigned int boundTexture[GraphicsCore::TEXTURE_SLOTS];
    private:
        static TextureDetails defaultDetails;
        friend class ResourceManager;

    };
}
#endif //CPPMC_TEXTURE_H
