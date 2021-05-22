//
// Created by Gerry on 2021-05-15.
//
#include <core/graphics/GraphicsCore.h>
#include "ViewManager.h"
#include "../../EngineCore/src/core/window/platforms/glfw/GLFWWindow.h"
#include <glad/glad.h> //TODO: change this to break out for different render engines!!!
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h> //TODO: change this to break out for different render engines!!!
#include <imgui/imgui_internal.h>

void ZitiView::ViewManager::setup(const Ref<Window> &window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    switch(GraphicsCore::api()) {
        case GraphicsAPI::OPENGL: {
            ImGui_ImplGlfw_InitForOpenGL(std::static_pointer_cast<GLFWWindow>(window)->ptr(),true);
            ImGui_ImplOpenGL3_Init("#version 130");
        }
    }

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

}

void ZitiView::ViewManager::clear() {
    ImGui_ImplGlfw_Shutdown();
}

void ZitiView::ViewManager::render(Ref<ZitiView::View> &view) {
    view->render();
}

void ZitiView::ViewManager::begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ZitiView::ViewManager::finish() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui_ImplGlfw_NewFrame();
}

void ZitiView::ViewManager::dock() {
    ImGuiIO& io = ImGui::GetIO();
    ImGuiID dockspace_id = ImGui::GetID("Dockspace");
    if(!_inited && ImGui::DockBuilderGetNode(dockspace_id) == NULL) {
        ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace); // Add empty node
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
        ImGuiID dock_id_prop = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.30f, NULL, &dock_main_id);
        ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 1.0f, NULL, &dock_main_id);

        ImGui::DockBuilderDockWindow("Hierarchy", dock_id_prop);
        ImGui::DockBuilderDockWindow("Viewport", dock_id_bottom);
        ImGui::DockBuilderFinish(dockspace_id);
        _inited = true;
    }
    ImGui::DockSpace(dockspace_id);
}
