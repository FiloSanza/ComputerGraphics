#include "Entity.h"

#include "../RendererUtils.h"

namespace Engine {
	Entity::Entity(
		std::shared_ptr<VertexArray> vertex_array,
		ModelMatrixHandler model_matrix,
		glm::mat4 projection_matrix
	) : vertex_array(vertex_array),
		model_matrix_updated(true),
		projection_matrix_updated(true),
		model_matrix(std::make_shared<ModelMatrixHandler>(std::move(model_matrix))), 
		projection_matrix(projection_matrix)
	{ }

	void Entity::draw()
	{
		RendererUtils::draw(vertex_array);
	}

	void Entity::setProjectionMatrix(glm::mat4 matrix)
	{
		projection_matrix_updated = true;
		projection_matrix = matrix;
	}

	void Entity::setProjectionMatrixUpdated()
	{
		projection_matrix_updated = false;
	}

	std::shared_ptr<ModelMatrixHandler> Entity::getModelMatrixHandler()
	{
		return model_matrix;
	}

	glm::mat4 Entity::getModelMatrix()
	{
		return model_matrix->getModelMatrix();
	}

	glm::mat4 Entity::getProjectionMatrix() const
	{
		return projection_matrix;
	}

	bool Entity::needToUpdateProjectionMatrix() const
	{
		return projection_matrix_updated;
	}

	Entity Entity::createEntity(
		std::shared_ptr<VertexArray> vertex_array,
		ModelMatrixHandler model_matrix,
		glm::mat4 projection_matrix
	) {
		return Entity(vertex_array, model_matrix, projection_matrix);
	}

	void ModelMatrixHandler::translateBy(glm::vec3 delta)
	{
		translation = delta;
	}

	void ModelMatrixHandler::scaleBy(glm::vec3 scale)
	{
		this->scale = scale;
	}

	void ModelMatrixHandler::rotate(float angle)
	{
		rotation = angle;
	}

	glm::mat4 ModelMatrixHandler::getModelMatrix()
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, translation);
		model = glm::scale(model, scale);
		// Check
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0f));
		return model;
	}

}