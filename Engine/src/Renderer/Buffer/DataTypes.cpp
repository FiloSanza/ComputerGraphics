#include "DataTypes.h"

namespace Engine {
	uint32_t ShaderDataTypeToGLType(ShaderDataType shader_type) {
		return GL_FLOAT;
	}
	uint32_t GetShaderDataTypeSize(ShaderDataType type) {
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
}