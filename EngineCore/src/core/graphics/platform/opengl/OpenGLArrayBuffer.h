//
// Created by Gerry on 2020-08-13.
//

#ifndef CPPMC_OPENGLARRAYBUFFER_H
#define CPPMC_OPENGLARRAYBUFFER_H

#include <glad/glad.h>
#include <core/graphics/Buffer.h>

namespace Ziti {

    static unsigned int toOpenGLType(ElementType type) {
        switch(type) {
            case ElementType::float1:
            case ElementType::float2:
            case ElementType::float3:
            case ElementType::float4:
                return GL_FLOAT;
            case ElementType::mat3: return GL_FLOAT;
            case ElementType::mat4: return GL_FLOAT;
            case ElementType::int1:
            case ElementType::int2:
            case ElementType::int3:
            case ElementType::int4:
            case ElementType::boolean: return GL_INT;
        }
        return -1;
    }

    class OpenGLArrayBuffer: public ArrayBuffer {
    public:
        OpenGLArrayBuffer(unsigned int size);
        OpenGLArrayBuffer(float* data, unsigned int size);

        void bind() override;

        void unbind() override;

        void data(const void *data, unsigned int size) override;

        void setLayout(const BufferLayout &layout) override {_layout = layout;};

        const BufferLayout &getLayout() override {return _layout;};

        ~OpenGLArrayBuffer() override;
    private:
        BufferLayout _layout;
        unsigned int _bufferId;
    };
}


#endif //CPPMC_OPENGLARRAYBUFFER_H
