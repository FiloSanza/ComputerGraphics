#include "Spore.h"
#include "SpriteLoader.h"
#include "Engine/engine.h"

#include <ranges>

namespace Sprites {
	const std::string Spore::VERTEX_FILE = "..\\Assignment1\\res\\sprites\\spore.csv";
	const glm::vec3 Spore::OBJECT_CENTER = glm::vec3(0.0);
	const float Spore::OBJECT_RADIUS = 3;
	const float Spore::SHOOT_DELAY = 1500; // in ms
	const float Spore::SPEED = 1.5;
	const int Spore::MAX_LEVEL = 5;

	Spore::Spore(glm::vec3 pos, int life_points, std::shared_ptr<Engine::GraphicContext> context)
		: life_points(life_points), pos(pos - OBJECT_CENTER), is_active(true), context(context)
	{
		const auto window_options = context->getWindow()->getOptions();
		const auto color = glm::vec4(1.0, 0.87, 0.58, 1);
		const auto color_center = glm::vec4(0.96, 0.64, 0.26, 1);
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
		entity->setProjectionMatrix(glm::ortho(0.0f, (float)window_options.world_width, 0.0f, (float)window_options.world_height));
		entity->getModelMatrixHandler()->translateBy(pos);
		entity->getModelMatrixHandler()->scaleBy(glm::vec3(7, 7, 0));
	}

	bool Spore::isActive() const
	{
		return life_points > 0 && is_active;
	}

	float Spore::getX() const
	{
		return pos.x;
	}

	float Spore::getY() const
	{
		return pos.y;
	}

	void Spore::draw() const
	{
		context->getShaderProgram()->bind();
		entity->draw();
	}

	glm::vec3 Spore::getPos() const
	{
		return pos;
	}

	bool Spore::hit(const HittableSprite& other) const
	{
		return entity->hit(other.getEntity());
	}

	std::shared_ptr<Engine::HittableEntity> Spore::getEntity() const
	{
		return entity;
	}

	std::shared_ptr<Engine::GraphicContext> Spore::getGraphicsContext() const
	{
		return context;
	}

	bool Spore::shouldShot() const
	{
		return Engine::RendererUtils::getElapsedTime() - last_shot_timestamp >= SHOOT_DELAY;
	}

	void Spore::activate()
	{
		is_active = true;
	}

	void Spore::deactivate()
	{
		is_active = false;
	}

	void Spore::updateX(float x)
	{
		pos.x = x;
	}

	void Spore::updateY(float y)
	{
		pos.y = y;
	}

	void Spore::moveBy(glm::vec3 delta)
	{
		pos += delta;
	}

	void Spore::updateEntity()
	{
		float angle = ((int)Engine::RendererUtils::getElapsedTime() / 100) % 360;
		entity->getModelMatrixHandler()->rotate(angle);
	}

	void Spore::updateProjectionMatrix(glm::mat4 matrix)
	{
		entity->setProjectionMatrix(matrix);
	}

	void Spore::decreaseLifePoints()
	{
		life_points--;
	}

	void Spore::updateShootTimeStamp()
	{
		last_shot_timestamp = Engine::RendererUtils::getElapsedTime();
	}
}