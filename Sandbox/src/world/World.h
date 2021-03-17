

//
// Created by Gerry on 2021-02-23.
//

#ifndef CPPMC_WORLD_H
#define CPPMC_WORLD_H

#include <glm/detail/type_vec2.hpp>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <scene/Entity.h>

using namespace VoxEng;
namespace VoxEng {
    class Timestep;
}
class IChunk;
class IChunkCreator;
struct KeyFuncsVec2i
{
    size_t operator()(const vec2i& k)const
    {
        return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
    }

    bool operator()(const vec2i& a, const vec2i& b)const
    {
        return a.x == b.x && a.y == b.y;
    }
};
typedef std::unordered_map<vec2i,Ref<IChunk>,KeyFuncsVec2i,KeyFuncsVec2i> ChunkMap;
class World {
public:
    World(Scope<IChunkCreator>& chunkCreator);

    void follow(Entity& follow);
	void viewDistance(float dist);
	
	void update(Timestep step);

    Ref<IChunk> getChunk(int x,int z);
	bool chunkExists(vec2i pos);
private:

	
    void fillNeighbors(vec2i pos, Ref<IChunk>& chunk);
	
    Scope<IChunkCreator> chunkCreator;
    std::vector<Ref<IChunk>> chunks;
    ChunkMap chunkMap;
    Entity following;
    float viewDist = 8;
};


#endif //CPPMC_WORLD_H
