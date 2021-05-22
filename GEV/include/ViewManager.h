//
// Created by Gerry on 2021-05-15.
//

#ifndef CPPMC_VIEWMANAGER_H
#define CPPMC_VIEWMANAGER_H

#include <core/window/Window.h>
#include <views/View.h>

using namespace Ziti;
namespace ZitiView {
    class ViewManager {
    public:
        void setup(const Ref<Window>& window);
        void render(Ref<View>& view);
        void begin();
        void dock();
        void finish();
        void clear();
    private:
        bool _inited = false;
    };
}


#endif //CPPMC_VIEWMANAGER_H
