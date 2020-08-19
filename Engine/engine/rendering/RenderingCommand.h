//
// Created by Gerry on 2020-08-12.
//

#ifndef CPPMC_RENDERINGCOMMAND_H
#define CPPMC_RENDERINGCOMMAND_H

namespace VoxEng {
    enum class BUFFER_BIT {
        COLOR = 0x00004000,
        DEPTH = 0x00000100,
        STENCIL = 0x00000400
    };

    inline BUFFER_BIT operator|(BUFFER_BIT a, BUFFER_BIT b)
    {
        return static_cast<BUFFER_BIT>(static_cast<int>(a) | static_cast<int>(b));
    }

    class RenderingCommand {
    public:
        static void clearScreenColor(float red, float green, float blue, float alpha);

        static void clear(BUFFER_BIT bit);

        static void viewport(int x, int y, int width, int height);
    };
}


#endif //CPPMC_RENDERINGCOMMAND_H