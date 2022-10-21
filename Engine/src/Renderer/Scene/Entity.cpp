#include "Entity.h"

#include "../RendererUtils.h"

namespace Engine {
	Entity::Entity(
		const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers,
		std::shared_ptr<IndexBuffer> index_buffer,
		DrawMode draw_mode,
		bool is_indexed,
		ModelMatrixHandler model_matrix,
		glm::mat4 projection_matrix
	) : model_matrix_updated(true),
		projection_matrix_updated(true),
		draw_mode(draw_mode),
		is_indexed(is_indexed),
		model_matrix(std::make_shared<ModelMatrixHandler>(std::move(model_matrix))), 
		projection_matrix(projection_matrix)
	{
		vertex_array = std::make_shared<VertexArray>();
		vertex_array->setIndexBuffer(index_buffer);

		for (const auto buffer : buffers) {
			vertex_array->addVertexBuffer(buffer);
		}
	}

	Entity::Entity(
		const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers, 
		uint32_t vertex_count,
		DrawMode draw_mode, 
		bool is_indexed, 
		ModelMatrixHandler model_matrix,
		glm::mat4 projection_matrix
	) : model_matrix_updated(true),
		projection_matrix_updated(true),
		draw_mode(draw_mode),
		is_indexed(is_indexed),
		model_matrix(std::make_shared<ModelMatrixHandler>(std::move(model_matrix))), 
		projection_matrix(projection_matrix)
	{
		vertex_array = std::make_shared<VertexArray>();
		vertex_array->setVertexCount(vertex_count);

		for (const auto buffer : buffers) {
			vertex_array->addVertexBuffer(buffer);
		}
	}

	void Entity::draw()
	{
		if (is_indexed) {
			RendererUtils::drawIndexed(vertex_array, draw_mode);
		}
		else {
			RendererUtils::draw(vertex_array, draw_mode);
		}
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
		const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers, 
		uint32_t vertex_count,
		DrawMode draw_mode, 
		ModelMatrixHandler model_matrix,
		glm::mat4 projection_matrix
	) {
		return Entity(buffers, vertex_count, draw_mode, false, model_matrix, projection_matrix);
	}

	Entity Entity::createIndexedEntity(
		const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers, 
		std::shared_ptr<IndexBuffer> index_buffer, 
		DrawMode draw_mode, 
		ModelMatrixHandler model_matrix,
		glm::mat4 projection_matrix
	) {
		return Entity(buffers, index_buffer, draw_mode, true, model_matrix, projection_matrix);
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