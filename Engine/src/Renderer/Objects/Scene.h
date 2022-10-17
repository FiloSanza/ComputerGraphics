#pragma once

#include <vector>
#include <memory>
#include "Object.h"
#include "../Shader/ShaderProgram.h"

namespace Engine {
	class Scene {
	public:
		Scene() {}
		Scene(std::shared_ptr<ShaderProgram> program);
		Scene(std::shared_ptr<ShaderProgram> program, std::initializer_list<std::shared_ptr<Object2D>> objects);

		void addObject(std::shared_ptr<Object2D> object);
		void draw();

	private:
		std::shared_ptr<ShaderProgram> program;
		std::vector<std::shared_ptr<Object2D>> objects;
	};
}