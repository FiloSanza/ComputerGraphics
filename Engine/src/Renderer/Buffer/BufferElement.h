#pragma once

#include <string>
#include "DataTypes.h"

namespace Engine {
	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t size;
		size_t offset;
		bool normalized;
	
		BufferElement() = default;

		BufferElement(std::string name, ShaderDataType type, bool normalized = false)
		 : name(name), type(type), size(GetShaderDataTypeSize(type)), offset(0), normalized(normalized) { }

		int getComponentCount() {
			switch (type) {
				case ShaderDataType::Float1: return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;
				default:
					return -1;
			}
		}
	};
}