#include "Entity.h"

#include "../RendererUtils.h"
#include <algorithm>
#include <iostream>


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

	Entity::Entity(
		std::shared_ptr<VertexArray> vertex_array,
		std::shared_ptr<ModelMatrixHandler> model_matrix,
		glm::mat4 projection_matrix
	) : vertex_array(vertex_array),
		model_matrix_updated(true),
		projection_matrix_updated(true),
		model_matrix(model_matrix),
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

	Entity Entity::createEntity(
		std::shared_ptr<VertexArray> vertex_array,
		std::shared_ptr<ModelMatrixHandler> model_matrix,
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

	float ModelMatrixHandler::getRotation() const
	{
		return rotation;
	}

	glm::vec3 ModelMatrixHandler::getScale() const
	{
		return scale;
	}

	glm::vec3 ModelMatrixHandler::getTranslation() const
	{
		return translation;
	}

	glm::mat4 ModelMatrixHandler::getModelMatrix() const
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, translation);
		model = glm::scale(model, scale);
		// Check
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0f));
		return model;
	}

	const glm::vec4 BoundingBox::BOUNDING_BOX_COLOR = glm::vec4(1.0, 0.0, 1.0, 1.0);

	BoundingBox::BoundingBox(glm::vec3 center, float radius, std::shared_ptr<ModelMatrixHandler> model_matrix)
		: center(center), radius(radius), model_matrix(model_matrix) {

		auto vertices = Geometry::Shapes::circumference(center, radius, 100, BOUNDING_BOX_COLOR);
		auto vbo_obj = VertexBuffer::createStatic(vertices);
		auto vbo = std::make_shared<VertexBuffer>(std::move(vbo_obj));
		auto vao = std::make_shared<VertexArray>();

		vbo->setLayout({
			{ "Position", Engine::ShaderDataType::Float3 },
			{ "Color", Engine::ShaderDataType::Float4 },
		});
		vao->addVertexBuffer(vbo);
		vao->setDrawSpecs({ {(uint32_t)vertices.size(), Engine::DrawMode::LineLoop} });
		bb_entity = Entity::createEntity(vao, model_matrix);
	}

	glm::vec3 BoundingBox::getCenter() const
	{
		const auto model = model_matrix->getModelMatrix();
		const auto transformed_center = model * glm::vec4(center, 1.0);
		return glm::vec3(
			transformed_center.x,
			transformed_center.y,
			transformed_center.z
		);
	}

	float BoundingBox::getRadius() const
	{
		return radius * glm::length(model_matrix->getScale());
	}

	void BoundingBox::draw()
	{
		 bb_entity.draw();
	}

	bool BoundingBox::checkIntersection(const BoundingBox& other) const
	{
		const float limit = getRadius() + other.getRadius();
		const float distance = glm::length(getCenter() - other.getCenter());
		//std::cout << "My center: [" << getCenter().x << ", " << getCenter().y << ", " << getCenter().z << "] Other center: [" << other.getCenter().x << ", " << other.getCenter().y << ", " << other.getCenter().z << "]\n";
		//std::cout << "Distance: " << distance << " Limit: " << limit << "\n";

		return distance < limit;
	}

	HittableEntity HittableEntity::createEntity(std::shared_ptr<VertexArray> vertex_array, glm::vec3 center, float radius, ModelMatrixHandler model_matrix, glm::mat4 projection_matrix)
	{
		return HittableEntity(vertex_array, center, radius, model_matrix, projection_matrix);
	}

	HittableEntity::HittableEntity(
		std::shared_ptr<VertexArray> vertex_array, 
		glm::vec3 center, 
		float radius, 
		ModelMatrixHandler model_matrix, 
		glm::mat4 projection_matrix
	) : Entity(vertex_array, model_matrix, projection_matrix)
	{
		bounding_box = BoundingBox(center, radius, this->model_matrix);
	}

	const BoundingBox& HittableEntity::getBoundingBox() const {
		return bounding_box;
	}

	void HittableEntity::drawWithBoundingBox() {
		bounding_box.draw();
		draw();
	}

	bool HittableEntity::hit(std::shared_ptr<Hittable> other) const {
		return bounding_box.checkIntersection(other->getBoundingBox());
	}

}