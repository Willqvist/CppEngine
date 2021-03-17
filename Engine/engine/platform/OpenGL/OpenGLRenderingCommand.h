//
// Created by Gerry on 2020-08-12.
//

#ifndef CPPMC_OPENGLRENDERINGCOMMAND_H
#define CPPMC_OPENGLRENDERINGCOMMAND_H


namespace VoxEng {

    enum class BUFFER_BIT;

    class OpenGLRenderingCommand {
    public:
        static void clearScreenColor(float red, float green, float blue, float alpha);

        static void clear(BUFFER_BIT bit);

        static void viewport(int x, int y, int width, int height);

    };
}


#endif //CPPMC_OPENGLRENDERINGCOMMAND_H
