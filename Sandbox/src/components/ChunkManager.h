//
// Created by Gerry on 2021-01-21.
//

#ifndef CPPMC_CHUNKMANAGER_H
#define CPPMC_CHUNKMANAGER_H
#include <scene/components/VoxComponent.h>
#include "CameraMovement.h"
#include "ChunkComponent.h"

using namespace VoxEng;
namespace VoxEng {
    class Scene;
}

typedef glm::ivec2 vec2i;

typedef std::unordered_map<glm::ivec2,Entity,IVec2KeyFuncs,IVec2KeyFuncs> ChunkMap;

class ChunkManager: public VoxEng::VoxComponent {
public:
    void onCreate() override;

    void setScene(Scene* scene);

    void setFollow(Entity e) {
        this->follow = e;
    }

    void update(VoxEng::Timestep ts) override {
    }




    void generate();

    void render() override {
        Renderer::render(chunk, mat, transform());
    }
private:
    Scene* scene;
    Entity follow;
    Ref<VertexArray> chunk;
    Ref<Material> mat;
};
#endif //CPPMC_CHUNKMANAGER_H
