//
// Created by Gerry on 2021-05-21.
//

#ifndef CPPMC_VIEWPORTVIEW_H
#define CPPMC_VIEWPORTVIEW_H

#include <views/View.h>
#include <TextureWindow.h>
#include <string>
using namespace Ziti;
namespace ZitiView {
    class ViewportView : public View {
    public:
        ViewportView(const std::string& name, Ref<TextureWindow>& texture);
        void render() override;
    private:
        Ref<TextureWindow> _texture;
        std::string _name;
    };
}


#endif //CPPMC_VIEWPORTVIEW_H
