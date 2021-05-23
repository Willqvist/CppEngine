//
// Created by Gerry on 2021-05-22.
//

#ifndef CPPMC_MESHRENDERER_H
#define CPPMC_MESHRENDERER_H

#include <core/graphics/Mesh.h>
#include <core/Memory.h>
#include "Spatial.h"

namespace Ziti {
    class MeshRenderer : public Spatial, public RenderTask {
        ISCLASS(MeshRenderer,Spatial)

        void start() override;

        void setMesh(const Ref<Mesh>& mesh);

        void setMaterial(Ref<Material>& mat);

        void render(RenderEngine &engine);

        void process(Ref<Camera> &camera, Ref<Material> &material, Transform &transform) override;

    private:
        
        Ref<Mesh> _mesh;
        Ref<Material> _material;
    };
}


#endif //CPPMC_MESHRENDERER_H
