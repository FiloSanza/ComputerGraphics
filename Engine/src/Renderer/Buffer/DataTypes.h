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

	uint32_t ShaderDataTypeToGLType(ShaderDataType shader_type);

	uint32_t GetShaderDataTypeSize(ShaderDataType type);

	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
	};

}