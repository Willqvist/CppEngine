//
// Created by Gerry on 2021-05-15.
//

#ifndef CPPMC_TEXTUREWINDOW_H
#define CPPMC_TEXTUREWINDOW_H

#include <core/window/Window.h>
#include <core/graphics/Texture.h>
#include <core/graphics/textures/RenderableTexture.h>

namespace Ziti {
    class TextureWindow : public Window {
    public:
        TextureWindow(FBOBuffers buffers, int width, int height);

        void enableVSync(bool enable) override;

        void update() override;

        void clear() override;

        int width() override;

        int height() override;

        void swap() override;

        void lockMouse(bool locked) override;

        void bind() override;

        void unbind() override;

        Ref<RenderableTexture> texture();

    private:
        Ref<RenderableTexture> _texture;
    };
}


#endif //CPPMC_TEXTUREWINDOW_H
