#include "Ghost.h"
#include "SpriteLoader.h"
#include "Engine/engine.h"

#include <ranges>

namespace Sprites {
	const std::string Ghost::VERTEX_FILE = "..\\Assignment1\\res\\sprites\\ghost.csv";
	const glm::vec3 Ghost::OBJECT_CENTER = glm::vec3(5.5, 7, 0.0);
	const float Ghost::OBJECT_RADIUS = 6;
	const float Ghost::SCALE_MULTIPLIER = 1.5;
	const float Ghost::SPEED = 1.5;
	const int Ghost::MAX_LEVEL = 5;

	Ghost::Ghost(glm::vec3 pos, int life_points, std::shared_ptr<Engine::GraphicContext> context)
		: life_points(life_points), pos(pos - OBJECT_CENTER), is_active(true), context(context)
	{
		const auto window_options = context->getWindow()->getOptions();
		const auto color = glm::vec4(0.8, 0.8, 0.8, 1);
		const auto color_center = glm::vec4(0.5, 0.5, 0.5, 1);
		auto points = SpriteLoader::load_sprite_coords(VERTEX_FILE);
		auto vertices = Geometry::Hermite::interpIntoVertices(points, { OBJECT_CENTER, color_center }, color, 140);

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

		auto obj = Engine::HittableEntity::createEntity(vertex_array, OBJECT_CENTER, OBJECT_RADIUS);
		entity = std::make_shared<Engine::HittableEntity>(obj);
		entity->setProjectionMatrix(glm::ortho(0.0f, (float)window_options.width, 0.0f, (float)window_options.height));
		entity->getModelMatrixHandler()->translateBy(pos);
	}

	bool Ghost::isActive() const
	{   
		return life_points > 0 && is_active;
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
		context->getShaderProgram()->bind();
		if (Engine::RendererUtils::isDebugModeEnabled())
			entity->draw();
		else
			entity->draw();
	}
	
	glm::vec3 Ghost::getPos() const
	{
		return pos;
	}

	bool Ghost::hit(const HittableSprite& other) const
	{
		return entity->hit(other.getEntity());
	}
	
	std::shared_ptr<Engine::HittableEntity> Ghost::getEntity() const
	{
		return entity;
	}

	std::shared_ptr<Engine::GraphicContext> Ghost::getGraphicsContext() const
	{
		return context;
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
	
	void Ghost::updateEntity()
	{
		moveBy(direction * SPEED);
		entity->getModelMatrixHandler()->scaleBy(glm::vec3(life_points * SCALE_MULTIPLIER, life_points * SCALE_MULTIPLIER, 0));
		entity->getModelMatrixHandler()->translateBy(pos);
	}

	void Ghost::setDirection(glm::vec3 direction)
	{
		this->direction = glm::normalize(direction);
	}
	
	void Ghost::decreaseLifePoints()
	{
		life_points--;
	}
}