#pragma once

#include <memory>

#include "../../lib.h"
#include "../Buffer/VertexArray.h"
#include "../Buffer/VertexBuffer.h"
#include "../Buffer/IndexBuffer.h"
#include "../Shader/ShaderProgram.h"

namespace Engine {
	class Object2D {
	public:
		Object2D(
			const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers,
			std::shared_ptr<IndexBuffer> index_buffer,
			glm::mat4 model_matrix, 
			glm::mat4 projection_matrix
		);

		void draw();

		void setModelMatrix(glm::mat4 matrix);
		void setProjectionMatrix(glm::mat4 matrix);
		void setModelMatrixUpdated();
		void setProjectionMatrixUpdated();
		glm::mat4 getModelMatrix() const;
		glm::mat4 getProjectionMatrix() const;
		bool needToUpdateModelMatrix() const;
		bool needToUpdateProjectionMatrix() const;


	private:
		std::shared_ptr<VertexArray> vertex_array;

		bool model_matrix_updated;
		bool projection_matrix_updated;
		glm::mat4 model_matrix;
		glm::mat4 projection_matrix;
	};
}