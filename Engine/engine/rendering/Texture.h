//
// Created by Gerry on 2020-08-12.
//

#ifndef CPPMC_TEXTURE_H
#define CPPMC_TEXTURE_H

#include "core/Core.h"
#include <core/GraphicsLibrary.h>
namespace VoxEng {

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

    struct TextureDetails {
        TextureType type = TextureType::T_2D;
        TextureWrap wrapping = TextureWrap::REPEAT;
        TextureFilter min = TextureFilter::NEAREST,max = TextureFilter::NEAREST;
    };

    class Texture {
    public:
        Texture(const TextureDetails& details);

        virtual void bind() = 0;
        virtual void bind(int location) = 0;
        virtual void unbind() = 0;
        virtual int width() = 0;
        virtual int height() = 0;

        virtual ~Texture() = default;

        TextureDetails details() {
            return mDetails;
        }

        virtual Ref<Texture> subTexture(int x,int y,int width,int height) = 0;

        static Ref<Texture> create(const char *path, const TextureDetails& details);
        static Ref<Texture> create(const char *path);
    protected:
        TextureDetails mDetails;
        inline static unsigned int boundTexture[GraphicsLibrary::TEXTURE_SLOTS];
    private:
        static TextureDetails defaultDetails;
        friend class ResourceManager;

    };
}
#endif //CPPMC_TEXTURE_H
