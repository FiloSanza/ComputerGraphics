#include "Shapes.h"

#include <numbers>

namespace Geometry {
	std::vector<Engine::Vertex> Shapes::circle(Engine::Vertex center, float radius, int n_points, glm::vec4 color)
	{
		const float center_x = center.position.x;
		const float center_y = center.position.y;
		std::vector<Engine::Vertex> vertices;
		vertices.push_back(center);

		float step = std::numbers::pi * 2.0 / n_points;
		for (int i = 0; i <= n_points; i++) {
			const float t = step * i;
			const float x = cos(t) * radius + center_x;
			const float y = sin(t) * radius + center_y;
			vertices.push_back({ glm::vec3(x, y, 0), color });
		}

		return vertices;
	}

	IndexedShape Shapes::rectangle(Engine::Vertex bottom_left, Engine::Vertex bottom_right, Engine::Vertex top_left, Engine::Vertex top_right)
	{
		std::vector<Engine::Vertex> vertices = {
			bottom_left,
			bottom_right,
			top_right,
			top_left
		};

		std::vector<uint32_t> indices = {0, 1, 2, 0, 2, 3};

		return { vertices, indices };
	}

	IndexedShape Shapes::rectangle(glm::vec3 bottom_left, glm::vec3 bottom_right, glm::vec3 top_left, glm::vec3 top_right, glm::vec4 color)
	{
		return Shapes::rectangle(
			{ bottom_left, color }, 
			{ bottom_right, color }, 
			{ top_left, color }, 
			{ top_right, color }
		);
	}

	std::vector<Engine::Vertex> Shapes::triangle(Engine::Vertex left, Engine::Vertex right, Engine::Vertex top)
	{
		return { left, right, top };
	}

	std::vector<Engine::Vertex> Shapes::triangle(glm::vec3 left, glm::vec3 right, glm::vec3 top, glm::vec4 color)
	{
		return Shapes::triangle(
			{ left, color },
			{ right, color },
			{ top, color }
		);
	}
}
