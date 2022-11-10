#include "TextRenderer.h"

namespace Engine {
	TextRenderer::TextRenderer(std::string font_file, std::shared_ptr<ShaderProgram> program)
		: program(program)
	{
		FT_Library ft;
		FT_Face face;

		if (FT_Init_FreeType(&ft))
		{
			// TODO: handle
			assert(false);
		}

		if (FT_New_Face(ft, font_file.c_str(), 0, &face))
		{
			printf("ERROR::FREETYPE: Failed to load font\n");
			assert(false);
		}
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				// TODO: handle
				fprintf(stderr, "ERROR::FREETYTPE: Failed to load Glyph \n");
				assert(false);
			}

			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			textures[c] = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>();

		std::shared_ptr<VertexBuffer> vbo 
			= std::make_shared<VertexBuffer>(VertexBuffer::createDynamic(6 * sizeof(TextureVertex)));

		vbo->setLayout({
			{ "Position", ShaderDataType::Float3 },
			{ "Texture Coords", ShaderDataType::Float2 }
		});

		vao->setDrawSpecs({ { 6, DrawMode::Triangles } });

		entity = DynamicEntity(vao, vbo);
	}

	void TextRenderer::setProjectionMatrix(glm::mat4 projection_matrix)
	{
		entity.setProjectionMatrix(projection_matrix);
	}

	void TextRenderer::drawText(std::string content, glm::vec4 color, glm::vec3 position, glm::vec3 scale, float angle)
	{
		program->bind();
		program->uploadUniformVec4("Color", color);
		
		// TODO: Refactor
		glActiveTexture(GL_TEXTURE0);

		for (const auto chr : content) {
			const auto& texture = textures[chr];

			float x	= position.x + texture.Bearing.x * scale.x;
			float y = position.y - (texture.Size.y - texture.Bearing.x) * scale.y;
			float w = texture.Size.x * scale.x;
			float h = texture.Size.y * scale.y;

			entity.setVertices({
				{{ x    , y + h, 0.0f }, { 0.0f, 0.0f }},
				{{ x    , y    , 0.0f }, { 0.0f, 1.0f }},
				{{ x + w, y    , 0.0f }, { 1.0f, 1.0f }},

				{{ x    , y + h, 0.0f }, { 0.0f, 0.0f }},
				{{ x + w, y    , 0.0f }, { 1.0f, 1.0f }},
				{{ x + w, y + h, 0.0f }, { 1.0f, 0.0f }},
			});

			// TODO: refactor
			glBindTexture(GL_TEXTURE_2D, texture.TextureID);
			
			entity.draw();
			position.x += (texture.Advance >> 6) * scale.x; // Move to the next character
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		program->unbind();
	}
}