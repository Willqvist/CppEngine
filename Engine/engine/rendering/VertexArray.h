//
// Created by Gerry on 2020-08-13.
//

#ifndef CPPMC_VERTEXARRAY_H
#define CPPMC_VERTEXARRAY_H

#include "Buffer.h"

namespace VoxEng {
    class VertexArray {
    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void addBuffer(const Ref<ArrayBuffer>& buffer) = 0;
        virtual void addIndexBuffer(const Ref<IndexBuffer>& buffer) = 0;

        virtual const Ref<IndexBuffer>& getIndexBuffer() = 0;
        const std::vector<Ref<ArrayBuffer>>& buffers() {return mBuffers; }
        virtual ~VertexArray() = default;
        static Ref<VertexArray> create();

    protected:
        std::vector<Ref<ArrayBuffer>> mBuffers;
    };
}


#endif //CPPMC_VERTEXARRAY_H
