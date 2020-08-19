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

    static unsigned int elementPrimativeSize(ElementType type) {
        switch(type) {
            case ElementType::float1: return 4;
            case ElementType::float2: return 4*2;
            case ElementType::float3: return 4*3;
            case ElementType::float4: return 4*4;
            case ElementType::mat3: return 4*3*3;
            case ElementType::mat4: return 4*4*4;
            case ElementType::int1: return 4;
            case ElementType::int2: return 4*2;
            case ElementType::int3: return 4*3;
            case ElementType::int4: return 4*4;
            case ElementType::boolean: return 1;
        }
        return -1;
    }

    class BufferElement {
    public:
        ElementType type;
        unsigned int size;
        unsigned int offset;
        bool normalized;
        BufferElement(ElementType type, bool normalized =false): type(type), size(elementPrimativeSize(type)), offset(0), normalized(normalized){}
        unsigned int count() const {
            switch(type) {
                case ElementType::float1: return 1;
                case ElementType::float2: return 2;
                case ElementType::float3: return 3;
                case ElementType::float4: return 4;
                case ElementType::mat3: return 3;
                case ElementType::mat4: return 4;
                case ElementType::int1: return 1;
                case ElementType::int2: return 2;
                case ElementType::int3: return 3;
                case ElementType::int4: return 4;
                case ElementType::boolean: return 1;
            }
            return -1;
        }
    };

    class BufferLayout {
    public:
        unsigned int mStride;
        BufferLayout(){}

        BufferLayout(const std::initializer_list<BufferElement> elements): mElements(elements) {
            calculateElements();
        }

        unsigned int stride() const {return mStride;}
        const std::vector<BufferElement>& elements() const { return mElements; }

    private:
        std::vector<BufferElement> mElements;
        void calculateElements() {
            int offset = 0;
            mStride = 0;
            for(BufferElement& e : mElements) {
                e.offset = offset;
                offset += e.size;
                mStride += e.size;
            }
        }
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
