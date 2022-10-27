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

		float getRotation() const;
		glm::vec3 getScale() const;
		glm::vec3 getTranslation() const;
		glm::mat4 getModelMatrix() const;

	private:
		glm::vec3 translation;
		glm::vec3 scale;
		float rotation;
	};

	class BoundingBox {
	public:
		BoundingBox() : center(glm::vec3(0)), radius(0) {}
		BoundingBox(glm::vec3 center, float radius, std::shared_ptr<ModelMatrixHandler> model_matrix)
			: center(center), radius(radius), model_matrix(model_matrix) {}

		glm::vec3 getCenter() const;
		float getRadius() const;

		bool checkIntersection(const BoundingBox& other) const;
	private:
		std::shared_ptr<ModelMatrixHandler> model_matrix;
		glm::vec3 center;
		float radius;
	};

	class Hittable {
	public:
		virtual bool hit(std::shared_ptr<Hittable> other) const = 0;
		virtual const BoundingBox& getBoundingBox() const = 0;
	};

	class Entity {
	public:
		Entity() = delete;

		void draw();

		std::shared_ptr<ModelMatrixHandler> getModelMatrixHandler();

		void setProjectionMatrix(glm::mat4 matrix);
		void updateVertexArray(std::shared_ptr<VertexArray> new_vertex_array);

		static Entity createEntity(
			std::shared_ptr<VertexArray> vertex_array,
			ModelMatrixHandler model_matrix = ModelMatrixHandler(),
			glm::mat4 projection_matrix = glm::mat4()
		);

	protected:
		Entity(
			std::shared_ptr<VertexArray> vertex_array,
			ModelMatrixHandler model_matrix,
			glm::mat4 projection_matrix
		);

		std::shared_ptr<VertexArray> vertex_array;

		bool model_matrix_updated;
		bool projection_matrix_updated;
		glm::mat4 projection_matrix;
		std::shared_ptr<ModelMatrixHandler> model_matrix;

	};

	class HittableEntity : public Entity, public Hittable {
	public:
		HittableEntity() = delete;

		bool hit(std::shared_ptr<Hittable> other) const override;
		const BoundingBox& getBoundingBox() const override;

		static HittableEntity createEntity(
			std::shared_ptr<VertexArray> vertex_array,
			glm::vec3 center,
			float radius,
			ModelMatrixHandler model_matrix = ModelMatrixHandler(),
			glm::mat4 projection_matrix = glm::mat4()
		);
	private:
		HittableEntity(
			std::shared_ptr<VertexArray> vertex_array,
			glm::vec3 center,
			float radius,
			ModelMatrixHandler model_matrix,
			glm::mat4 projection_matrix
		);

		BoundingBox bounding_box;
	};
}