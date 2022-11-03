#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../Renderer/Buffer/DataTypes.h"

namespace Geometry {
	class Hermite {
	public:
		static std::vector<Engine::Vertex> interpIntoVertices(
			const std::vector<glm::vec3>& points,
			Engine::Vertex center,
			glm::vec4 color_vertex,
			int samples
		);
	private:
		static float derive(int idx, const std::vector<float>& t, const auto& value);
		static float derive(int idx, const std::vector<float>& t, float delta_prev, float delta_next, float tens = 0, float bias = 0, float cont = 0);
		static inline float phi0(const float t);
		static inline float phi1(const float t);
		static inline float psi0(const float t);
		static inline float psi1(const float t);
	};
}