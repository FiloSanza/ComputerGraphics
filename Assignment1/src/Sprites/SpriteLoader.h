#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace Sprites {
	class SpriteLoader {
	public:
		static std::vector<glm::vec3> load_sprite_coords(const std::string& path);
	};
}

