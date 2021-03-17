#pragma once
#include <glm/vec3.hpp>
#include <core/Core.h>
#include <scene/components/Transform.h>

#define DEBUG_SIZE 10000
namespace VoxEng {

    class Material;
    class VertexArray;
    class ArrayBuffer;
    class IndexBuffer;

	class DebugRenderer
	{
	public:
		static void init();
		static void drawCube(glm::vec3 p1, glm::vec3 p7, int color);
		static void drawLines(const std::initializer_list<glm::vec3>& points, int color);
		
		static void drawLine(glm::vec3 c1, glm::vec3 c2, glm::vec3 color);
		static void drawFace(glm::vec3 c1, glm::vec3 c2,glm::vec3 normal, int color);
		static void flush();
	private:
		static void appendPoint(const glm::vec3& p, int color);
		
		static Ref<VertexArray> vao;
		static Ref<ArrayBuffer> dataBuffer;
		static Ref<IndexBuffer> indexBuffer;
		static Ref<Material> material;
		static Transform transform;
		static float data[DEBUG_SIZE];
		static unsigned int indicies[DEBUG_SIZE];
		static int cIdx;
		static int index;
	};
}
