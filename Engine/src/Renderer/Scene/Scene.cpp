#include "Scene.h"

namespace Engine {
	Scene::Scene(std::shared_ptr<ShaderProgram> program) 
		: program(program), objects({}) {}
	
	Scene::Scene(std::shared_ptr<ShaderProgram> program, std::initializer_list<std::shared_ptr<Entity>> objects)
		: program(program), objects(objects) {}
	
	void Scene::addObject(std::shared_ptr<Entity> object) {
		objects.push_back(object);
	}
	
	void Scene::draw() {
		for (auto obj : objects) {
			program->uploadUniformMat4("Model", obj->getModelMatrix());

			if (obj->needToUpdateProjectionMatrix()) {
				program->uploadUniformMat4("Projection", obj->getProjectionMatrix());
				obj->setProjectionMatrixUpdated();
			}

			obj->draw();
		}
	}
}