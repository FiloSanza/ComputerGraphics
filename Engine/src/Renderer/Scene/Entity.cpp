#include "Entity.h"

#include "../RendererUtils.h"

namespace Engine {
	Entity::Entity(
		const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers,
		std::shared_ptr<IndexBuffer> idx_buffer,
		glm::mat4 model_matrix, 
		glm::mat4 projection_matrix
	) : model_matrix_updated(true), 
		projection_matrix_updated(true), 
		model_matrix(model_matrix), 
		projection_matrix(projection_matrix)
	{
		vertex_array = std::make_shared<VertexArray>();
		vertex_array->setIndexBuffer(idx_buffer);

		for (const auto buffer : buffers) {
			vertex_array->addVertexBuffer(buffer);
		}
	}

	void Entity::draw()
	{
		RendererUtils::drawIndexed(vertex_array);
	}

	void Entity::setModelMatrix(glm::mat4 matrix)
	{
		model_matrix_updated = true;
		model_matrix = matrix;
	}

	void Entity::setProjectionMatrix(glm::mat4 matrix)
	{
		projection_matrix_updated = true;
		projection_matrix = matrix;
	}

	void Entity::setModelMatrixUpdated() 
	{
		model_matrix_updated = false;
	}

	void Entity::setProjectionMatrixUpdated()
	{
		projection_matrix_updated = false;
	}

	glm::mat4 Entity::getModelMatrix() const
	{
		return model_matrix;
	}

	glm::mat4 Entity::getProjectionMatrix() const
	{
		return projection_matrix;
	}

	bool Entity::needToUpdateModelMatrix() const
	{
		return model_matrix_updated;
	}

	bool Entity::needToUpdateProjectionMatrix() const
	{
		return projection_matrix_updated;
	}


}