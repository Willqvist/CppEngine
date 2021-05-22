//
// Created by Gerry on 2021-05-06.
//

#ifndef CPPMC_VIEWPORT_H
#define CPPMC_VIEWPORT_H

namespace Ziti {
    class Viewport {
    public:
        Viewport(int width,int height) : _width(width),_height(height){}
        virtual int width() {return _width;}
        virtual int height() {return _height;}
    private:
        int _width,_height;
    };
}


#endif //CPPMC_VIEWPORT_H
