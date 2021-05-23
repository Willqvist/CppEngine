//
// Created by Gerry on 2021-05-21.
//

#include <imgui/imgui.h>
#include "ViewportView.h"
#include "../../../EngineCore/src/core/graphics/platform/opengl/OpenGLTexture.h"

void ZitiView::ViewportView::render() {
    Ref<RenderableTexture> tex = _texture->texture();
    Ref<OpenGLTexture> _col = std::static_pointer_cast<OpenGLTexture>(tex->getBufferTexture(FBOBuffers::COLOR));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin(_name.c_str());
    ImGui::PopStyleVar();
    ImVec2 wSize = ImGui::GetWindowSize();
    ImVec2 size = ImGui::GetContentRegionAvail();
    ImVec2 oSize = size;
    ImVec2 imgSize = ImVec2(_col->width(),_col->height());
    float ratio = imgSize.x/imgSize.y;
    float wRatio = size.x/size.y;
    ImVec2 rSize = wRatio > ratio ? ImVec2(imgSize.x*size.y/imgSize.y,size.y) : ImVec2(size.x,imgSize.y*size.x/imgSize.x);
    /*
    if(oSize.x < imgSize.x) {
        float aspect = imgSize.x/imgSize.y;
        size.y = size.x/aspect;
        imgSize.y = size.y;
        imgSize.x = size.x;
    }
    */
    size = rSize;
    ImGui::SetCursorPos(ImVec2((oSize.x-size.x)*0.5f + wSize.x - oSize.x,(oSize.y-size.y)*0.5f + wSize.y - oSize.y));
    ImGui::Image((void*)(intptr_t)_col->textureId(),size);
    ImGui::End();
}

ZitiView::ViewportView::ViewportView(const std::string& name, Ref<TextureWindow> &texture) : _name(name), _texture(texture) {}