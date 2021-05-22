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
    ImVec2 vMin = ImGui::GetWindowContentRegionMin();
    ImVec2 vMax = ImGui::GetWindowContentRegionMax();

    ImVec2 size = ImVec2(vMax.x-vMin.x,vMax.y-vMin.y);

    ImGui::Image((void*)(intptr_t)_col->textureId(),size);
    ImGui::End();
}

ZitiView::ViewportView::ViewportView(const std::string& name, Ref<TextureWindow> &texture) : _name(name), _texture(texture) {}