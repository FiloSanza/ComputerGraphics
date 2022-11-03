#pragma once

#include <memory>

#include "../../lib.h"
#include "../../../engine.h"

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

	class Entity {
	public:
		Entity() {}

		void draw();

		std::shared_ptr<ModelMatrixHandler> getModelMatrixHandler();

		void setProjectionMatrix(glm::mat4 matrix);
		void updateVertexArray(std::shared_ptr<VertexArray> new_vertex_array);

		static Entity createEntity(
			std::shared_ptr<VertexArray> vertex_array,
			ModelMatrixHandler model_matrix = ModelMatrixHandler(),
			glm::mat4 projection_matrix = glm::mat4()
		);

		static Entity createEntity(
			std::shared_ptr<VertexArray> vertex_array,
			std::shared_ptr<ModelMatrixHandler> model_matrix,
			glm::mat4 projection_matrix = glm::mat4()
		);

	protected:
		Entity(
			std::shared_ptr<VertexArray> vertex_array,
			ModelMatrixHandler model_matrix,
			glm::mat4 projection_matrix
		);

		Entity(
			std::shared_ptr<VertexArray> vertex_array,
			std::shared_ptr<ModelMatrixHandler> model_matrix,
			glm::mat4 projection_matrix = glm::mat4()
		);

		std::shared_ptr<VertexArray> vertex_array;

		bool model_matrix_updated;
		bool projection_matrix_updated;
		glm::mat4 projection_matrix;
		std::shared_ptr<ModelMatrixHandler> model_matrix;

	};

	class BoundingBox {
	public:
		BoundingBox() : center(glm::vec3(0)), radius(0) {}
		BoundingBox(glm::vec3 center, float radius, std::shared_ptr<ModelMatrixHandler> model_matrix);

		void draw();

		glm::vec3 getCenter() const;
		float getRadius() const;
		bool checkIntersection(const BoundingBox& other) const;
	private:
		static const glm::vec4 BOUNDING_BOX_COLOR;

		std::shared_ptr<ModelMatrixHandler> model_matrix;
		Entity bb_entity;
		glm::vec3 center;
		float radius;
	};

	class Hittable {
	public:
		virtual bool hit(std::shared_ptr<Hittable> other) const = 0;
		virtual const BoundingBox& getBoundingBox() const = 0;
	};

	class HittableEntity : public Entity, public Hittable {
	public:
		HittableEntity() = delete;

		bool hit(std::shared_ptr<Hittable> other) const override;
		const BoundingBox& getBoundingBox() const override;

		void drawWithBoundingBox();

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