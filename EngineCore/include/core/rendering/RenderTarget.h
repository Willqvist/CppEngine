//
// Created by Gerry on 2021-05-08.
//

#ifndef CPPMC_RENDERTARGET_H
#define CPPMC_RENDERTARGET_H

#include "Viewport.h"

namespace Ziti {
    class RenderTarget {
    public:
        Viewport& viewport() {
            return _viewport;
        }
        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void clear() = 0;

        void setViewport(int width,int height)  {
            _viewport = Viewport(width,height);
        }
    private:
        Viewport _viewport = Viewport(0,0);
    };
}


#endif //CPPMC_RENDERTARGET_H
