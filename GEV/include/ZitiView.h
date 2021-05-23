//
// Created by Gerry on 2021-05-14.
//

#ifndef CPPMC_ZITIVIEW_H
#define CPPMC_ZITIVIEW_H

#include <core/app/Application.h>
#include <views/View.h>
#include "ViewManager.h"
#include "TextureWindow.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
using namespace Ziti;
namespace ZitiView {
    class ZitiView : public Application {
    public:
        ZitiView(Scope<Application>& app);
        void start() override;

        void update() override;

        void render(Ziti::RenderEngine &engine) override;

        void stop() override;

        void postRender() override;

    private:

        void renderViews() {
            _manager.begin();
            ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("DockSpace Demo",0,flags);
            ImGui::PopStyleVar();
            _manager.dock();
            for(auto& view : _views) {
                _manager.render(view);
            }
            ImGui::End();
            ImGui::PopStyleVar();
            //_manager.finish();
        }

        template<class T, class ... Args>
        Ref<T> addView(Args&& ... args) {
            Ref<T> view = CreateRef<T>(std::forward<Args>(args)...);
            _views.push_back(view);
            return view;
        }

        std::vector<Ref<View>> _views;
        ViewManager _manager;
        Scope<Application> _app;
        Ref<TextureWindow> _gameWindow;
        Ref<TextureWindow> _editorWindow;
    };
}


#endif //CPPMC_ZITIVIEW_H
