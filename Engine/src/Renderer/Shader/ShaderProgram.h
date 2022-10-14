#pragma once

#include <stdint.h>
#include <string>

#include "../../lib.h"

namespace Engine {
	enum class ShaderType {
		VERTEX = 0,
		FRAGMENT
	};

	class ShaderProgram
	{
	public:
		ShaderProgram() {}
		ShaderProgram(std::string vertex_shader_path, std::string fragment_shader_path);

		void bind() const;
		void unbind() const;

		void uploadUniformMat4(std::string name, glm::mat4 mat);
	private:
		static uint32_t compileShader(std::string path, ShaderType type);
		static uint32_t getShaderTypeValue(ShaderType type);
		static std::string getShaderTypeString(ShaderType type);
		void createProgram(uint32_t vertex_shader_id, uint32_t fragment_shader_id);

		uint32_t id;
	};
}

