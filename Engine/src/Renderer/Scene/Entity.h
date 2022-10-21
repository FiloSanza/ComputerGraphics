#pragma once

#include <memory>

#include "../../lib.h"
#include "../Buffer/VertexArray.h"
#include "../Buffer/VertexBuffer.h"
#include "../Buffer/IndexBuffer.h"
#include "../Shader/ShaderProgram.h"
#include "../Buffer/DataTypes.h"

namespace Engine {
	class Entity {
	public:
		Entity() = delete;
		Entity(Entity&) = delete;
		Entity(Entity&&) = delete;

		void draw();

		void setModelMatrix(glm::mat4 matrix);
		void setProjectionMatrix(glm::mat4 matrix);
		void setModelMatrixUpdated();
		void setProjectionMatrixUpdated();
		glm::mat4 getModelMatrix() const;
		glm::mat4 getProjectionMatrix() const;
		bool needToUpdateModelMatrix() const;
		bool needToUpdateProjectionMatrix() const;

		static Entity createEntity(
			const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers,
			DrawMode draw_mode,
			glm::mat4 model_matrix = glm::mat4(),
			glm::mat4 projection_matrix = glm::mat4()
		);

		static Entity createIndexedEntity(
			const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers,
			std::shared_ptr<IndexBuffer> index_buffer,
			DrawMode draw_mode,
			glm::mat4 model_matrix = glm::mat4(),
			glm::mat4 projection_matrix = glm::mat4()
		);
	private:
		Entity(
			const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers,
			std::shared_ptr<IndexBuffer> index_buffer,
			DrawMode draw_mode,
			bool is_indexed,
			glm::mat4 model_matrix,
			glm::mat4 projection_matrix
		);

		Entity(
			const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers,
			DrawMode draw_mode,
			bool is_indexed,
			glm::mat4 model_matrix,
			glm::mat4 projection_matrix
		);

		std::shared_ptr<VertexArray> vertex_array;

		bool is_indexed;
		DrawMode draw_mode;
		bool model_matrix_updated;
		bool projection_matrix_updated;
		glm::mat4 model_matrix;
		glm::mat4 projection_matrix;
	};
}