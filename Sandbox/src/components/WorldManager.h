//
// Created by Gerry on 2021-02-23.
//

#ifndef CPPMC_WORLDMANAGER_H
#define CPPMC_WORLDMANAGER_H

#include <scene/components/VoxComponent.h>
#include <memory>
#include "../world/IChunkCreator.h"
using namespace std;

class IChunk;
class World;

using namespace VoxEng;
class WorldManager: public VoxComponent, public IChunkCreator {
public:
    void onCreate() override;

	void rebuildChunk(Ref<IChunk>& chunk);
	void follow(Entity& follow);
	void update(Timestep ts) override;
    Ref<IChunk> createChunk(int x,int y);

private:
    Ref<World> world;	
};


#endif //CPPMC_WORLDMANAGER_H
