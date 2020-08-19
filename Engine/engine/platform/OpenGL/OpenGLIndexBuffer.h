//
// Created by Gerry on 2020-08-16.
//

#ifndef CPPMC_OPENGLINDEXBUFFER_H
#define CPPMC_OPENGLINDEXBUFFER_H

#include <rendering/Buffer.h>

namespace VoxEng {
    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        unsigned int getSize() override;

        OpenGLIndexBuffer(const unsigned int *data, unsigned int size);
        OpenGLIndexBuffer(unsigned int size);

        void bind() override;

        void unbind() override;

        void data(const unsigned int *data, unsigned int size) override;

        ~OpenGLIndexBuffer() override;

    private:
        unsigned int bufferId;
        unsigned int size;
    };
}


#endif //CPPMC_OPENGLINDEXBUFFER_H
