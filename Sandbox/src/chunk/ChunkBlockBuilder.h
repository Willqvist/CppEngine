//
// Created by Gerry on 2020-09-08.
//

#ifndef CPPMC_CHUNKBLOCKBUILDER_H
#define CPPMC_CHUNKBLOCKBUILDER_H


#include "Chunk.h"
#include <pipeline/PipelineObject.h>
#include <threading/ThreadPool.h>
#include "glm/vec2.hpp"
class ChunkComponent;

class ChunkBlockBuilder : public PipelineObject<Ref<ChunkComponent>,Ref<ChunkComponent>> {
public:
    static Ref<ChunkBlockBuilder>& instance();

	void follow(Entity& following);

    void generate(const Ref<Chunk>& chunk,glm::vec2 worldPos);

    void threads(int num);

    ChunkBlockBuilder(ChunkBlockBuilder const&) = delete;
    void operator=(ChunkBlockBuilder const&)  = delete;

protected:
    void onInsert(Ref<ChunkComponent> &val) override;

private:
    ChunkBlockBuilder() {}
    Entity following;
    ThreadPool<Ref<ChunkComponent>>* threadPool = nullptr;
};


#endif //CPPMC_CHUNKBLOCKBUILDER_H
