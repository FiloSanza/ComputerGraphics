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
		ShaderProgram(): id(0), is_binded(false) {}
		ShaderProgram(const std::string vertex_shader_path, const std::string fragment_shader_path);

		void bind();
		void unbind();

		void uploadUniformMat4(std::string name, glm::mat4 mat) const;
		void uploadUniformFloat(std::string name, float value) const;
		void uploadUniformVec2(std::string name, glm::vec2 vec) const;
		void uploadUniformVec4(std::string name, glm::vec4 vec) const;
		static const ShaderProgram* getActiveInstance();
	private:
		void createProgram(uint32_t vertex_shader_id, uint32_t fragment_shader_id);
		static uint32_t compileShader(std::string path, ShaderType type);
		static uint32_t getShaderTypeValue(ShaderType type);
		static std::string getShaderTypeString(ShaderType type);

		uint32_t id;
		bool is_binded;
		static const ShaderProgram* active_program;
	};
}

