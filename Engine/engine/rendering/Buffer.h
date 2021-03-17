//
// Created by Gerry on 2020-08-13.
// inspiration from Hazel Engine: https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Renderer/Buffer.h
//

#ifndef CPPMC_BUFFER_H
#define CPPMC_BUFFER_H

#include <core/Core.h>
#include "Vertex.h"
#include <vector>

namespace VoxEng {

    enum class ElementType {
        none=0,float1,float2,float3,float4,mat3,mat4,int1,int2,int3,int4,boolean
    };

    class BufferElement {
    public:
        ElementType type;
        unsigned int size;
        unsigned int offset;
        bool normalized;
        BufferElement(ElementType type, bool normalized =false);
        unsigned int count() const;
    };

    class BufferLayout {
    public:
        unsigned int mStride;
        BufferLayout(){}

        BufferLayout(const std::initializer_list<BufferElement> elements);

        unsigned int stride() const;
        const std::vector<BufferElement>& elements() const;

    private:
        std::vector<BufferElement> mElements;
        void calculateElements();
    };

    class ArrayBuffer {
    public:

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void data(const void* data, unsigned int size) = 0;
        virtual void setLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& getLayout() = 0;
        static Ref<ArrayBuffer> create(unsigned int size);
        static Ref<ArrayBuffer> create(float* vertices, unsigned int size);

        virtual ~ArrayBuffer() = default;
        int size;
    };

    class IndexBuffer {
    public:

        IndexBuffer() {}

        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual unsigned int getSize() = 0;
        virtual void data(const unsigned int* data, unsigned int size) = 0;
        static Ref<IndexBuffer> create(unsigned int size);
        static Ref<IndexBuffer> create(unsigned int* vertices, unsigned int size);

        virtual ~IndexBuffer() = default;

    };
}

#endif //CPPMC_BUFFER_H
