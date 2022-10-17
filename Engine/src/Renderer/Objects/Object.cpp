#include "Object.h"

#include "../RendererUtils.h"

namespace Engine {
	Object2D::Object2D(
		const std::vector<std::shared_ptr<VertexBuffer>>& buffers,
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

	void Object2D::draw()
	{
		RendererUtils::drawIndexed(vertex_array);
	}

	void Object2D::setModelMatrix(glm::mat4 matrix)
	{
		model_matrix_updated = true;
		model_matrix = matrix;
	}

	void Object2D::setProjectionMatrix(glm::mat4 matrix)
	{
		projection_matrix_updated = true;
		projection_matrix = matrix;
	}

	void Object2D::setModelMatrixUpdated() 
	{
		model_matrix_updated = false;
	}

	void Object2D::setProjectionMatrixUpdated()
	{
		projection_matrix_updated = false;
	}

	glm::mat4 Object2D::getModelMatrix() const
	{
		return model_matrix;
	}

	glm::mat4 Object2D::getProjectionMatrix() const
	{
		return projection_matrix;
	}

	bool Object2D::needToUpdateModelMatrix() const
	{
		return model_matrix_updated;
	}

	bool Object2D::needToUpdateProjectionMatrix() const
	{
		return projection_matrix_updated;
	}


}