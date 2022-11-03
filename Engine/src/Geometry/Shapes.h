#pragma once

#include "../Renderer/Buffer/DataTypes.h"
#include <vector>
#include <glm/glm.hpp>

namespace Geometry {
	struct IndexedShape {
		std::vector<Engine::Vertex> vertices;
		std::vector<uint32_t> indices;
	};

	class Shapes {
	public: 
		static std::vector<Engine::Vertex> circle(Engine::Vertex center, float radius, int n_points, glm::vec4 color);
		static std::vector<Engine::Vertex> circumference(glm::vec3 center, float radius, int n_points, glm::vec4 color);
		static IndexedShape rectangle(glm::vec3 bottom_left, glm::vec3 top_right, glm::vec4 color);
		static std::vector<Engine::Vertex> triangle(Engine::Vertex left, Engine::Vertex right, Engine::Vertex top);
		static std::vector<Engine::Vertex> triangle(glm::vec3 left, glm::vec3 right, glm::vec3 top, glm::vec4 color);
	};
}

