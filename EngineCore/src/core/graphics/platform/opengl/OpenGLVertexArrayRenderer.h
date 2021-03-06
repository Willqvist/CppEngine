//
// Created by Gerry on 2020-08-16.
//

#ifndef CPPMC_OPENGLVERTEXARRAYRENDERER_H
#define CPPMC_OPENGLVERTEXARRAYRENDERER_H

#include <core/Memory.h>
namespace Ziti {
	class VertexArray;
    class OpenGLVertexArrayRenderer {
    public:
        static void draw(Ref<VertexArray> &buffer, int mode);
    };
}


#endif //CPPMC_OPENGLVERTEXARRAYRENDERER_H
