//
// Created by Gerry on 2021-05-14.
//

#include <core/graphics/GraphicsCommand.h>
#include <imgui/imgui.h>
#include "ZitiView.h"
#include "views/NodeHierarchyView.h"
#include "views/ViewportView.h"

int dockspace_id = 0;

void ZitiView::ZitiView::start() {
    //TODO: create TextureWindow!! instead of window;
    _texWindow = CreateRef<TextureWindow>(FBOBuffers::COLOR |FBOBuffers::DEPTH, 1980,1080);
    _app->init(_texWindow);
    _manager.setup(window());
    addView<NodeHierarchyView>(_app->getNodeTree());
    addView<ViewportView>("Viewport",_texWindow);

    _app->start();

    //TODO: move this to custom io manager!!!
}

void ZitiView::ZitiView::update() {
    _app->update();
}

void ZitiView::ZitiView::render(Ziti::RenderEngine &engine) {
    GraphicsCommand::clearScreenColor(0.2,0.5,0.8,1);
    GraphicsCommand::clear(BUFFER_BIT::COLOR | BUFFER_BIT::DEPTH);
    _app->render(engine);
}

void ZitiView::ZitiView::stop() {
    _app->update();
}

ZitiView::ZitiView::ZitiView(Scope<Application> &app) : _app(std::move(app)) {

}


void ZitiView::ZitiView::postRender() {
    _app->postRender();
    /*
    ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
    flags |= ImGuiWindowFlags_NoDocking;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
     */
    //ImGui::Begin("DockSpace Demo");
    //ImGui::PopStyleVar();
    //ImGui::End();
    renderViews();
    /*
    Ref<RenderableTexture> tex = _texWindow->texture();
    Ref<OpenGLTexture> _col = std::static_pointer_cast<OpenGLTexture>(tex->getBufferTexture(FBOBuffers::COLOR));
    ImGui::Begin("image");
    ImGui::Image((void*)(intptr_t)_col->textureId(),ImVec2(200,200));
    ImGui::End();

    ImGui::End();
     */
    _manager.finish();
}
