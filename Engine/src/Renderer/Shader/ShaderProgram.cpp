#include "ShaderProgram.h"
#include "../../Utils/Files.h"
#include "../../Exceptions/ShaderLoadException.h"

#include <iostream>
#include <sstream>
#include <vector>

namespace Engine {
	ShaderProgram::ShaderProgram(const std::string vertex_shader_path, const std::string fragment_shader_path)
		: is_binded(false)
	{
		auto vertex_shader_id = ShaderProgram::compileShader(vertex_shader_path, ShaderType::VERTEX);
		auto fragment_shader_id = ShaderProgram::compileShader(fragment_shader_path, ShaderType::FRAGMENT);

		int error_code = glGetError();
		if (error_code != GL_NO_ERROR && error_code != GL_INVALID_ENUM) {
			std::stringstream error_buf;
			error_buf << "Error: could not create the shader.\n"
				<< "Error message : "
				<< gluErrorString(error_code);
			throw new ShaderLoadException(error_buf.str());
		}

		createProgram(vertex_shader_id, fragment_shader_id);
	}

	void ShaderProgram::bind()
	{
		if (is_binded)
			return;
		glUseProgram(id);
		active_program = this;
		is_binded = true;
	}

	void ShaderProgram::unbind()
	{
		glUseProgram(0);
		is_binded = false;
	}

	void ShaderProgram::uploadUniformMat4(std::string name, glm::mat4 mat) const
	{
		auto location = glGetUniformLocation(id, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void ShaderProgram::uploadUniformFloat(std::string name, float value) const
	{
		auto location = glGetUniformLocation(id, name.c_str());
		glUniform1f(location, value);
	}

	void ShaderProgram::uploadUniformVec2(std::string name, glm::vec2 vec) const
	{
		auto location = glGetUniformLocation(id, name.c_str());
		glUniform2f(location, vec.x, vec.y);
	}

	void ShaderProgram::uploadUniformVec4(std::string name, glm::vec4 vec) const
	{
		auto location = glGetUniformLocation(id, name.c_str());
		glUniform4f(location, vec.r, vec.g, vec.b, vec.a);
	}

	const ShaderProgram* ShaderProgram::getActiveInstance()
	{
		return active_program;
	}

	uint32_t ShaderProgram::compileShader(std::string path, ShaderType type)
	{
		std::string source = File::readAllAsString(path);
		const char* source_str = source.c_str();
		uint32_t shader_id = glCreateShader(ShaderProgram::getShaderTypeValue(type));
	
		glShaderSource(shader_id, 1, &source_str, nullptr);
		glCompileShader(shader_id);

		int success;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
		if (!success) {
			int32_t max_log_length;
			glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &max_log_length);
			std::vector<GLchar> log(max_log_length);
			glGetShaderInfoLog(shader_id, max_log_length, nullptr, log.data());

			std::stringstream error_buf;
			error_buf << "ERROR - Shader compilation failed.\n"
				<< "Shader type: " + ShaderProgram::getShaderTypeString(type) + "\n"
				<< log.empty() ? "" : log.data();
			throw new ShaderLoadException(error_buf.str());
		}

		return shader_id;
	}

	void ShaderProgram::createProgram(uint32_t vertex_shader_id, uint32_t fragment_shader_id)
	{
		id = glCreateProgram();
		glAttachShader(id, vertex_shader_id);
		glAttachShader(id, fragment_shader_id);

		glLinkProgram(id);

		int32_t is_linked;
		glGetProgramiv(id, GL_LINK_STATUS, &is_linked);
		if (is_linked == GL_FALSE) {
			int32_t max_log_length;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &max_log_length);
			std::vector<GLchar> log(max_log_length);
			glGetShaderInfoLog(id, max_log_length, nullptr, log.data());
		
			glDeleteProgram(id);
			glDeleteShader(vertex_shader_id);
			glDeleteShader(fragment_shader_id);

			std::stringstream error_buf;
			error_buf << "ERROR - Shader linking failed.\n"
				<< log.data();
			throw new ShaderLoadException(error_buf.str());
		}

		glDetachShader(id, vertex_shader_id);
		glDetachShader(id, fragment_shader_id);
		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);
	}
	
	uint32_t ShaderProgram::getShaderTypeValue(ShaderType type)
	{
		switch (type) {
		case ShaderType::FRAGMENT:
			return GL_FRAGMENT_SHADER;
		case ShaderType::VERTEX:
			return GL_VERTEX_SHADER;
		// TODO: assert
		default:
			return -1;
		}
	}

	std::string ShaderProgram::getShaderTypeString(ShaderType type)
	{
		switch (type) {
		case ShaderType::FRAGMENT:
			return "FRAGMENT";
		case ShaderType::VERTEX:
			return "VERTEX";
			// TODO: assert
		default:
			return "";
		}
	}

	const ShaderProgram* ShaderProgram::active_program = nullptr;
}
