//
// Created by Gerry on 2021-05-08.
//

#ifndef CPPMC_TESTVIEWAPP_H
#define CPPMC_TESTVIEWAPP_H


#include <core/app/Application.h>
#include <core/graphics/Material.h>
#include <core/graphics/textures/RenderableTexture.h>
#include <core/Memory.h>
#include <core/scene/Camera3D.h>
#include "CubeTest.h"

class TestViewApp : public Ziti::Application {
public:
    void start() override;

    void update() override;

    void render(Ziti::RenderEngine &engine) override;

    void stop() override;

    void renderGizmos(Ziti::RenderEngine &engine) override;

private:
    CubeTest* _cube;
    Ziti::Ref<Ziti::RenderableTexture> _rtex;
    Ziti::Ref<Ziti::Material> _mat, _mat2;
    Ziti::Ref<Ziti::Camera> _camera, _cam2;
    Ziti::Ref<Ziti::Camera3D> _cameraNode;
};


#endif //CPPMC_TESTVIEWAPP_H
