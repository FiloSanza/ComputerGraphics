#pragma once

#include <memory>

#include "../../lib.h"
#include "../Buffer/VertexArray.h"
#include "../Buffer/VertexBuffer.h"
#include "../Buffer/IndexBuffer.h"
#include "../Shader/ShaderProgram.h"
#include "../Buffer/DataTypes.h"

namespace Engine {
	class ModelMatrixHandler {
	public:
		ModelMatrixHandler()
		  : translation(glm::vec3()),
			rotation(0),
			scale(glm::vec3(1.0))
		{}

		void translateBy(glm::vec3 delta);
		void scaleBy(glm::vec3 scale);
		/**
		 * Angle in degrees.
		 */
		void rotate(float angle);

		glm::mat4 getModelMatrix();

	private:
		glm::vec3 translation;
		glm::vec3 scale;
		float rotation;
	};

	class Entity {
	public:
		Entity() = delete;

		void draw();

		std::shared_ptr<ModelMatrixHandler> getModelMatrixHandler();
		glm::mat4 getModelMatrix();
		glm::mat4 getProjectionMatrix() const;
		bool needToUpdateProjectionMatrix() const;

		void setProjectionMatrix(glm::mat4 matrix);
		void setProjectionMatrixUpdated();

		static Entity createEntity(
			const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers,
			uint32_t vertex_count,
			DrawMode draw_mode,
			ModelMatrixHandler model_matrix = ModelMatrixHandler(),
			glm::mat4 projection_matrix = glm::mat4()
		);

		static Entity createIndexedEntity(
			const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers,
			std::shared_ptr<IndexBuffer> index_buffer,
			DrawMode draw_mode,
			ModelMatrixHandler model_matrix = ModelMatrixHandler(),
			glm::mat4 projection_matrix = glm::mat4()
		);

	private:
		Entity(
			const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers,
			std::shared_ptr<IndexBuffer> index_buffer,
			DrawMode draw_mode,
			bool is_indexed,
			ModelMatrixHandler model_matrix, 
			glm::mat4 projection_matrix
		);

		Entity(
			const std::initializer_list<std::shared_ptr<VertexBuffer>>& buffers,
			uint32_t vertex_count,
			DrawMode draw_mode,
			bool is_indexed,
			ModelMatrixHandler model_matrix, 
			glm::mat4 projection_matrix
		);

		std::shared_ptr<VertexArray> vertex_array;

		bool is_indexed;
		DrawMode draw_mode;
		bool model_matrix_updated;
		bool projection_matrix_updated;
		glm::mat4 projection_matrix;
		std::shared_ptr<ModelMatrixHandler> model_matrix;
	};
}