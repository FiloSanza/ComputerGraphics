#include "Player.h"

#include <iostream>

namespace Sprites {
	const glm::vec3 Player::OBJECT_CENTER = glm::vec3(0, 0, 0);
	const float Player::OBJECT_RADIUS = 1;

	Player::Player(glm::vec3 pos, std::shared_ptr<Engine::GraphicContext> context)
		: pos(pos), is_active(true), angle(0), context(context)
	{
		auto window_options = context->getWindow()->getOptions();
		auto color = glm::vec4(0, 0, 1, 1.0);
		auto vertices = Geometry::Shapes::circle({ glm::vec3(0, 0, 0), color }, 1, 200, color);

		int circle_size = vertices.size();

		vertices.push_back({ glm::vec3(1.4,  0.5, 0.0), color });
		vertices.push_back({ glm::vec3(1.4, -0.5, 0.0), color });
		vertices.push_back({ glm::vec3(0,   0, 0.0), color });

		auto vbo_obj = Engine::VertexBuffer::createStatic(vertices);
		auto vertex_vbo = std::make_shared<Engine::VertexBuffer>(std::move(vbo_obj));
		auto vertex_array = std::make_shared<Engine::VertexArray>();

		vertex_vbo->setLayout({
			{ "Position", Engine::ShaderDataType::Float3 },
			{ "Color", Engine::ShaderDataType::Float4 },
		});

		vertex_array->addVertexBuffer(vertex_vbo);
		vertex_array->setDrawSpecs({
			{ (uint32_t)circle_size, Engine::DrawMode::TriangleFan },
			{ (uint32_t)vertices.size() - circle_size, Engine::DrawMode::Triangles }
		});

		entity = std::make_shared<Engine::HittableEntity>(
			Engine::HittableEntity::createEntity(vertex_array, OBJECT_CENTER, OBJECT_RADIUS)
		);

		entity->getModelMatrixHandler()->translateBy(pos);
		entity->getModelMatrixHandler()->scaleBy(glm::vec3(30, 30, 0));
		entity->setProjectionMatrix(glm::ortho(0.0f, (float)window_options.world_width, 0.0f, (float)window_options.world_height));
	}

	bool Player::isActive() const
	{
		return is_active;
	}

	float Player::getX() const
	{
		return pos.x;
	}

	float Player::getY() const
	{
		return pos.y;
	}
	
	void Player::draw() const
	{
		context->getShaderProgram()->bind();
		entity->draw();
	}
	
	glm::vec3 Player::getPos() const
	{
		return pos;
	}

	bool Player::hit(const HittableSprite& other) const
	{
		return entity->hit(other.getEntity());
	}
	
	std::shared_ptr<Engine::HittableEntity> Player::getEntity() const
	{
		return entity;
	}

	std::shared_ptr<Engine::GraphicContext> Player::getGraphicsContext() const
	{
		return context;
	}
	
	void Player::activate()
	{
		is_active = true;
	}
	
	void Player::deactivate()
	{
		is_active = false;
	}

	void Player::updateX(float delta_x)
	{
		pos.x += delta_x;
	}

	void Player::updateY(float delta_y)
	{
		pos.x += delta_y;
	}

	void Player::moveBy(glm::vec3 delta)
	{
		pos += delta;
	}

	void Player::rotateBy(float angle)
	{
		this->angle = angle;
	}
	
	void Player::updateEntity()
	{
		entity->getModelMatrixHandler()->translateBy(pos);
		entity->getModelMatrixHandler()->rotate(angle);
	}
	
	void Player::updateProjectionMatrix(glm::mat4 matrix)
	{
		entity->setProjectionMatrix(matrix);
	}
}