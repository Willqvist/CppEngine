//
// Created by Gerry on 2020-09-08.
//

#ifndef CPPMC_CHUNKMODELBUILDER_H
#define CPPMC_CHUNKMODELBUILDER_H


#include <threading/ThreadPool.h>
#include <pipeline/PipelineObject.h>
#include <rendering/Buffer.h>
#include "tools/DataPool.h"

class ChunkComponent;

namespace VoxEng {
    class VertexArray;
}

struct GeneratedData {
    std::vector<float> data, uvData;
    std::vector<unsigned int> indicies;
};

using BuildCallback = std::function<void(Ref<VertexArray>& vao)>;

struct ChunkQueueData {
    Ref<ChunkComponent> chunk;
};

struct GeneratePointers {
    float* vertices;
    float* uvs;
    unsigned int* indicies;
    int vertexSize, uvSize, indexSize;
};


struct MainThreadDataRet {
    Ref<ChunkComponent> queueData;
    GeneratePointers ptrs;
    int id;
};

struct ChunkModelBuilderData {
    Ref<ChunkComponent> chunkComp;
    Ref<VertexArray> data;
};


namespace VoxEng {

    class ChunkModelBuilder : public PipelineObject<Ref<ChunkComponent>,ChunkModelBuilderData> {
    public:

        static Ref<ChunkModelBuilder>& instance();

        void threads(int num);

        static void wow(std::vector<float>& uvData);

        void follow(Entity& following);
    	
        ChunkModelBuilder(ChunkModelBuilder const&) = delete;
        void operator=(ChunkModelBuilder const&)  = delete;

    private:

    protected:
        void onInsert(Ref<ChunkComponent> &val) override;

    private:

        ChunkModelBuilder();
        void generate(Chunk& c,GeneratePointers* ptrs);

        const BufferLayout layout = BufferLayout({
            BufferElement(ElementType::float3)
        });

        const BufferLayout uvLayout = BufferLayout({
            BufferElement(ElementType::float2)
        });

        GeneratePointers getPointers(int pool);
        void returnData(GeneratePointers& ptrs);
        void buildingChunk(Ref<ChunkComponent>& c, int threadId);

        DataPool<float, 200000,10> vertexPool;
        DataPool<float, 200000,10> uvPool;
        DataPool<unsigned int, 150000,10> indiciesPool;
        ThreadPool<Ref<ChunkComponent>>* threadPool = nullptr;
        Entity following;
    };
}

#endif //CPPMC_CHUNKMODELBUILDER_H
