//
// Created by Gerry on 2021-02-23.
//

#ifndef CPPMC_ICHUNKCREATOR_H
#define CPPMC_ICHUNKCREATOR_H
#include "core/Core.h"
using namespace VoxEng;
class IChunkCreator {
public:
    virtual Ref<IChunk> createChunk() = 0;
};
#endif //CPPMC_ICHUNKCREATOR_H
