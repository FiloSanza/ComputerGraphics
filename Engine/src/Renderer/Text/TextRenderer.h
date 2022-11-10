#pragma once

#include <map>
#include <string>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../Entities/Entity.h"

namespace Engine {
	class TextRenderer {
	public:
		TextRenderer() {}
		TextRenderer(std::string font_file, std::shared_ptr<ShaderProgram> program);
		void setProjectionMatrix(glm::mat4 projection_matrix);
		void drawText(std::string content, glm::vec4 color, glm::vec3 position, glm::vec3 scale, float angle = 0);
	private:
		struct Character {
			unsigned int TextureID; // ID handle of the glyph texture
			glm::ivec2   Size;      // Size of glyph
			glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
			unsigned int Advance;   // Horizontal offset to advance to next glyph
		};

		std::shared_ptr<ShaderProgram> program;
		std::map<char, Character> textures;
		DynamicEntity entity;
	};
}