//
// Created by Gerry on 2020-09-08.
//

#ifndef CPPMC_CHUNKMODELBUILDER_H
#define CPPMC_CHUNKMODELBUILDER_H


#include <tools/ThreadPool.h>
#include "Chunk.h"
#include "tools/DataPool.h"

namespace VoxEng {
    class ChunkModelBuilder {
    public:
        static void threads(int num) {
            if(threadPool != nullptr) {
                delete threadPool;
            }
            threadPool = new ThreadPool<Chunk>(num);
        }

        static void build(Chunk &c) {
            threadPool->run(buildingChunk, c);
        }

    private:

        static void buildingChunk(Chunk& c) {
            int size = sizeof(c.getBlocks())*8;
            float* data = vertexPool.Rent(size);
            vertexPool.Return(data,size);
        }

        static inline DataPool<float, 10000 * 5> vertexPool;
        static inline ThreadPool<Chunk>* threadPool;
    };
}

#endif //CPPMC_CHUNKMODELBUILDER_H
