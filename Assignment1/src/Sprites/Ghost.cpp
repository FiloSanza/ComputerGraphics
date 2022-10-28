#include "Ghost.h"
#include "../Geometry/Shapes.h"
#include "../Geometry/Hermite.h"

namespace Sprites {
	const std::string Ghost::VERTEX_FILE = "..\\..\\res\\sprites\\ghost.csv";

	Ghost::Ghost(float screen_width, float screen_height)
		: pos(glm::vec3(0)), is_active(true)
	{
		const auto color = glm::vec4(1, 0, 0, 1);
		auto vertices = Geometry::Shapes::circle({ pos, color }, 1, 100, color);

		auto vbo_obj = Engine::VertexBuffer::createStatic(vertices);
		auto vertex_vbo = std::make_shared<Engine::VertexBuffer>(std::move(vbo_obj));
		auto vertex_array = std::make_shared<Engine::VertexArray>();

		vertex_vbo->setLayout({
			{ "Position", Engine::ShaderDataType::Float3 },
			{ "Color", Engine::ShaderDataType::Float4 },
		});
		vertex_array->addVertexBuffer(vertex_vbo);
		vertex_array->setDrawSpecs({
			{ (uint32_t)vertices.size(), Engine::DrawMode::TriangleFan },
		});

		auto obj = Engine::HittableEntity::createEntity(vertex_array, pos, 1);
		entity = std::make_shared<Engine::HittableEntity>(obj);
		entity->setProjectionMatrix(glm::ortho(0.0f, screen_width, 0.0f, screen_height));
		entity->getModelMatrixHandler()->scaleBy(glm::vec3(50, 50, 0));
		entity->getModelMatrixHandler()->translateBy(glm::vec3(400, 400, 0));
	}

	bool Ghost::isActive() const
	{
		return is_active;
	}
	
	float Ghost::getX() const
	{
		return pos.x;
	}
	
	float Ghost::getY() const
	{
		return pos.y;
	}
	
	void Ghost::draw() const
	{
		entity->draw();
	}
	
	glm::vec3 Ghost::getPos() const
	{
		return pos;
	}

	bool Ghost::hit(const std::shared_ptr<Engine::HittableEntity>& other) const
	{
		return entity->hit(other);
	}
	
	void Ghost::activate()
	{
		is_active = true;
	}
	
	void Ghost::deactivate()
	{
		is_active = false;
	}
	
	void Ghost::updateX(float x)
	{
		pos.x = x;
	}
	
	void Ghost::updateY(float y)
	{
		pos.y = y;
	}
	
	void Ghost::moveBy(glm::vec3 delta)
	{
		pos += delta;
	}
}