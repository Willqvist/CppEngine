//
// Created by Gerry on 2020-08-13.
//

#ifndef CPPMC_OPENGLVERTEXARRAY_H
#define CPPMC_OPENGLVERTEXARRAY_H


#include <core/graphics/VertexArray.h>

namespace Ziti {
    class OpenGLVertexArray: public VertexArray {
    public:

        OpenGLVertexArray();

        void bind() override;

        void unbind() override;

        const Ref<IndexBuffer> &getIndexBuffer() override;

        void addBuffer(const Ref<ArrayBuffer> &buffer) override;

        void addIndexBuffer(const Ref<IndexBuffer> &buffer) override;

        ~OpenGLVertexArray() override;

    private:
        unsigned int _vaoId;
        unsigned int _vertexIndex = 0;
        Ref<IndexBuffer> _indexBuffer;
    };
}


#endif //CPPMC_OPENGLVERTEXARRAY_H
