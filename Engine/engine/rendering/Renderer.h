//
// Created by Gerry on 2020-08-18.
//

#ifndef CPPMC_RENDERER_H
#define CPPMC_RENDERER_H

#include <core/Core.h>
#include <stack>
namespace VoxEng {

    class Camera;
    enum RenderMode;
    class VertexArray;
    class Transform;
    class Material;

    class Renderer {
    public:
        static void begin(Camera* camera);
        static void pushMode(RenderMode mode);
        static void popMode();
        static void render(Ref <VertexArray> array,Ref<Material> material, Transform& transform);
        static void end();
    private:
        static Camera* camera;
        static std::stack<RenderMode> _mode;
    };
}


#endif //CPPMC_RENDERER_H
