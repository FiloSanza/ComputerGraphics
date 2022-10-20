#pragma once

#include <vector>
#include <memory>
#include "Entity.h"
#include "../Shader/ShaderProgram.h"

namespace Engine {
	class Scene {
	public:
		Scene() {}
		Scene(std::shared_ptr<ShaderProgram> program);
		Scene(std::shared_ptr<ShaderProgram> program, std::initializer_list<std::shared_ptr<Entity>> objects);

		void addObject(std::shared_ptr<Entity> object);
		void draw();

	private:
		std::shared_ptr<ShaderProgram> program;
		std::vector<std::shared_ptr<Entity>> objects;
	};
}