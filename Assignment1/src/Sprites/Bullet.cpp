#pragma once

#include "Bullet.h"

namespace Sprites {
	const glm::vec3 Bullet::OBJECT_CENTER = glm::vec3(0, 0, 0);
	const float Bullet::OBJECT_RADIUS = 1;
	const float Bullet::SPEED = 10;

	Bullet::Bullet(glm::vec3 pos, glm::vec3 direction, std::shared_ptr<Engine::GraphicContext> context)
		: pos(pos + OBJECT_CENTER), is_active(true), direction(direction), context(context)
	{
		auto window_options = context->getWindow()->getOptions();
		auto color = glm::vec4(0, 0, 1, 1.0);
		auto vertices = Geometry::Shapes::circle({ glm::vec3(0, 0, 0), color }, 1, 6, color);

		auto vbo_obj = Engine::VertexBuffer::createStatic(vertices);
		auto vertex_vbo = std::make_shared<Engine::VertexBuffer>(std::move(vbo_obj));
		auto vertex_array = std::make_shared<Engine::VertexArray>();

		vertex_vbo->setLayout({
			{ "Position", Engine::ShaderDataType::Float3 },
			{ "Color", Engine::ShaderDataType::Float4 },
		});
		vertex_array->addVertexBuffer(vertex_vbo);
		vertex_array->setDrawSpecs({{ (uint32_t)vertices.size(), Engine::DrawMode::TriangleFan }});

		entity = std::make_shared<Engine::HittableEntity>(
			Engine::HittableEntity::createEntity(vertex_array, OBJECT_CENTER, OBJECT_RADIUS)
		);
		entity->setProjectionMatrix(glm::ortho(0.0f, (float)window_options.width, 0.0f, (float)window_options.height));
		entity->getModelMatrixHandler()->scaleBy(glm::vec3(5, 5, 0));
		entity->getModelMatrixHandler()->translateBy(pos);
	}

	bool Bullet::isActive() const
	{
		return is_active;
	}
	
	float Bullet::getX() const
	{
		return pos.x;
	}
	
	float Bullet::getY() const
	{
		return pos.y;
	}

	void Bullet::draw() const
	{
		context->getShaderProgram()->bind();
		if (Engine::RendererUtils::isDebugModeEnabled())
			entity->draw();
		else
			entity->draw();
	}
	
	glm::vec3 Bullet::getPos() const
	{
		return pos;
	}
	
	bool Bullet::hit(const HittableSprite& other) const
	{
		return entity->hit(other.getEntity());
	}
	
	std::shared_ptr<Engine::HittableEntity> Bullet::getEntity() const
	{
		return entity;
	}

	std::shared_ptr<Engine::GraphicContext> Bullet::getGraphicsContext() const
	{
		return context;
	}
	
	void Bullet::activate()
	{
		is_active = true;
	}
	
	void Bullet::deactivate()
	{
		is_active = false;
	}
	
	void Bullet::updateX(float delta_x)
	{
		pos.x += delta_x;
	}
	
	void Bullet::updateY(float delta_y)
	{
		pos.y += delta_y;
	}
	
	void Bullet::moveBy(glm::vec3 delta)
	{
		pos += delta;
	}

	void Bullet::updateEntity() 
	{
		moveBy(direction * SPEED);
		entity->getModelMatrixHandler()->translateBy(pos);
	}
	
	void Bullet::setDirecton(glm::vec3 direction)
	{
		this->direction = glm::normalize(direction);
	}
}