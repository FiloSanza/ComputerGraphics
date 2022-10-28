#include "SpriteLoader.h"

#include <ranges>
#include <charconv>
#include <string_view>
#include "Engine/engine.h"

namespace Sprites {

	std::vector<glm::vec3> SpriteLoader::load_sprite_coords(const std::string& path) {
		std::vector<glm::vec3> output;
		auto file_content = Engine::File::readAllAsString(path);
		auto file_lines = std::string_view{ file_content }
			| std::views::split('\n');

		const auto parse_to_float = [](const auto& s) -> float {
			float value;
			const auto view = std::string_view{ s.begin(), s.end() };
			std::from_chars(view.data(), view.data() + view.size(), value);
			return value;
		};

		for (const auto& line : file_lines) {
			auto values_view = line 
				| std::views::split(',')
				| std::views::transform(parse_to_float);
			auto values = std::vector<float>(values_view.begin(), values_view.end());
			output.emplace_back(values[0], values[1], values[2]);
		}

		return output;
	}

}