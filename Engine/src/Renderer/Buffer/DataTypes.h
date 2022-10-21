#pragma once

#include "../../lib.h"
#include <cstdint>

namespace Engine {
	enum class ShaderDataType {
		None = 0,
		Float1,
		Float2,
		Float3,
		Float4
	};

	static uint32_t ShaderDataTypeToGLType(ShaderDataType shader_type) {
		return GL_FLOAT;
	}

	static uint32_t GetShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::None:   return 0;
		case ShaderDataType::Float1: return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		default:
			return -1;
		}
	}

	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
	};

	enum class DrawMode {
		/**
		 * A line is drawn using vertices 0 and 1, then 2 and 3 and so on... 
		 */
		Lines,
		/**
		 * A line is drawn using vertices 0 and 1, then 1 and 2 and so on...
	   	 */
		LineStrip,
		/**
		 * Like LineStrip but the last line is connected with the first one creating a loop 
		 */
		LineLoop,
		/**
		 * A triangle is created with vertices 0, 1 and 2, then another one with 3, 4, 5 and so on...
		 */
		Triangles,
		/**
		 * A triangle is created with vertices 0, 1, 2 and then another one with 1, 2 3 and so on...
		 */
		TriangleStrip,
		/**
		 * Like Triangles but vertex 0 is always used. Example: Triangle 1 (0, 1, 2), Triangle 2 (0, 3, 4) and so on...
		 */
		TriangleFan
	};

	static uint32_t drawModeToGLMode(DrawMode mode) {
		switch (mode) {
		case DrawMode::Lines:			return GL_LINES;
		case DrawMode::LineStrip:		return GL_LINE_STRIP;
		case DrawMode::LineLoop:		return GL_LINE_LOOP;
		case DrawMode::Triangles:		return GL_TRIANGLES;
		case DrawMode::TriangleStrip:	return GL_TRIANGLE_STRIP;
		case DrawMode::TriangleFan:		return GL_TRIANGLE_FAN;
		}
	}
}