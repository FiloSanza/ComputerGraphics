#include "Entity.h"

#include "../RendererUtils.h"
#include <algorithm>

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
		RendererUtils::uploadUniformMat4("Model", model_matrix->getModelMatrix());

		if (projection_matrix_updated) {
			RendererUtils::uploadUniformMat4("Projection", projection_matrix);
			projection_matrix_updated = false;
		}

		RendererUtils::draw(vertex_array);
	}

	void Entity::setProjectionMatrix(glm::mat4 matrix)
	{
		projection_matrix_updated = true;
		projection_matrix = matrix;
	}

	void Entity::updateVertexArray(std::shared_ptr<VertexArray> new_vertex_array)
	{
		vertex_array = new_vertex_array;
	}

	std::shared_ptr<ModelMatrixHandler> Entity::getModelMatrixHandler()
	{
		return model_matrix;
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

	glm::vec3 BoundingBox::bottomLeft() const
	{
		return bottom_left;
	}

	glm::vec3 BoundingBox::topRight() const
	{
		return top_right;
	}

	bool BoundingBox::checkIntersection(const BoundingBox& other) const
	{
		return bottom_left.x < other.topRight().x
			&& top_right.x > other.bottomLeft().x
			&& bottom_left.y < other.topRight().y
			&& top_right.y > other.bottomLeft().y;
	}

	HittableEntity HittableEntity::createEntity(std::shared_ptr<VertexArray> vertex_array, glm::vec3 bottom_left, glm::vec3 top_right, ModelMatrixHandler model_matrix, glm::mat4 projection_matrix)
	{
		return HittableEntity(vertex_array, bottom_left, top_right, model_matrix, projection_matrix);
	}

	HittableEntity::HittableEntity(
		std::shared_ptr<VertexArray> vertex_array, 
		glm::vec3 bottom_left, 
		glm::vec3 top_right, 
		ModelMatrixHandler model_matrix, 
		glm::mat4 projection_matrix
	) : Entity(vertex_array, model_matrix, projection_matrix),
		bounding_box(BoundingBox(bottom_left, top_right))
	{ }

	const BoundingBox& HittableEntity::getBoundingBox() const {
		return bounding_box;
	}

	bool HittableEntity::hit(const std::shared_ptr<Hittable>& other) const {
		return bounding_box.checkIntersection(other->getBoundingBox());
	}

}