#include "Scene.h"

namespace Engine {
	Scene::Scene(std::shared_ptr<ShaderProgram> program) 
		: program(program), objects({}) {}
	
	Scene::Scene(std::shared_ptr<ShaderProgram> program, std::initializer_list<std::shared_ptr<Object2D>> objects)
		: program(program), objects(objects) {}
	
	void Scene::addObject(std::shared_ptr<Object2D> object) {
		objects.push_back(object);
	}
	
	void Scene::draw() {
		for (auto obj : objects) {
			if (obj->needToUpdateModelMatrix()) {
				program->uploadUniformMat4("Model", obj->getModelMatrix());
				obj->setModelMatrixUpdated();
			}

			if (obj->needToUpdateProjectionMatrix()) {
				program->uploadUniformMat4("Projection", obj->getProjectionMatrix());
				obj->setProjectionMatrixUpdated();
			}

			obj->draw();
		}
	}
}