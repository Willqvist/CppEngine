//
// Created by Gerry on 2021-05-25.
//

#ifndef CPPMC_ZITIEDITORRENDERENGINE_H
#define CPPMC_ZITIEDITORRENDERENGINE_H

#include <core/rendering/RenderEngine.h>
using namespace Ziti;
namespace ZitiView {
    class ZitiEditorRenderEngine : public RenderEngine {
    public:
        void setCamera(Ref<Camera> camera) override;

    private:
        void setEditorCamera(Ref<Camera> camera);
        friend class ZitiView;
    };
}


#endif //CPPMC_ZITIEDITORRENDERENGINE_H
