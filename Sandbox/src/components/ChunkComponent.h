//
// Created by Gerry on 2021-01-14.
//

#ifndef CPPMC_CHUNKCOMPONENT_H
#define CPPMC_CHUNKCOMPONENT_H

#include <scene/components/VoxComponent.h>
#include "../chunk/Chunk.h"

using namespace VoxEng;

class World;
namespace VoxEng {
    class Material;
    class VertexArray;
}

class ChunkComponent: public VoxComponent, public IChunk {
public:


    void setChunk(Ref<Chunk>& chunk,int x,int y);
    void setChunkProvider(Ref<World>& world);

    void build();

    void setView(Ref<VertexArray>& array);

    Ref<Chunk> getChunk();

    void onCreate() override;

    static Ref<ChunkComponent> create(Scene* scene, int x,int z);

    void isVisible(bool visible);

    vec2i worldPosition();

    bool isDirty();

    void setPosition(int x,int z);

    void render() override;

    ~ChunkComponent() override;

    Block getBlock(int x, int y, int z) override;
    void setBlock(int x, int y, int z, Block& block) override;
    Block* getBlocks() override;
    void setNeighbor(VoxEng::Ref<IChunk> chunk, int neigh) override;
    bool hasNeighbor(int neigh) override;

private:
    Ref<World> world;
    Ref<Chunk> chunk;
    Ref<VertexArray> vertexArray;
    Ref<Material> material;
    vec2i worldPos;
    bool visible = false;
};
#endif //CPPMC_CHUNKCOMPONENT_H
