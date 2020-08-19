//
// Created by Gerry on 2020-08-12.
//

#ifndef CPPMC_GRAPHICSLIBRARY_H
#define CPPMC_GRAPHICSLIBRARY_H
namespace VoxEng {
    enum class Library {
        OPENGL
    };

    class GraphicsLibrary {
    public:
        static Library& library() {
            return GraphicsLibrary::m_library;
        }
    public:
        inline static const unsigned int TEXTURE_SLOTS = 32;
    private:
        inline static Library m_library;
    };
}
#endif //CPPMC_GRAPHICSLIBRARY_H
