//
// Created by Gerry on 2020-08-18.
//

#ifndef CPPMC_RENDERER_H
#define CPPMC_RENDERER_H

#include <core/Material.h>
#include "VertexArray.h"

namespace VoxEng {
    class Renderer {
    public:
        static void begin(/*ComponentRef<Camera>& camera*/);
        static void render(Ref <VertexArray> array,Ref<Material> material);
        static void end();
    };
}


#endif //CPPMC_RENDERER_H
