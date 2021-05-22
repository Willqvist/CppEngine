//
// Created by Gerry on 2020-08-12.
//

#ifndef CPPMC_GRAPHICSLIBRARY_H
#define CPPMC_GRAPHICSLIBRARY_H
namespace Ziti {
    enum class GraphicsAPI {
        OPENGL, VULKAN
    };

    class GraphicsCore {
    public:
        static GraphicsAPI& api();
    public:
        inline static const unsigned int TEXTURE_SLOTS = 32;
    private:
        inline static GraphicsAPI _library;
    };
}
#endif //CPPMC_GRAPHICSLIBRARY_H
