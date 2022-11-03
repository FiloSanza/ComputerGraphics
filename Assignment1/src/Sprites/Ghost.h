#pragma once

#include "Sprite.h"
#include "Engine/engine.h"
#include <memory>
#include <string>

namespace Sprites {
	class Ghost : public HittableSprite {
	public:
		const static int MAX_LEVEL;

		Ghost() : is_active(false) {}
		Ghost(glm::vec3 pos, int life_points, std::shared_ptr<Engine::GraphicContext> context);

		bool isActive() const;
		float getX() const;
		float getY() const;
		void draw() const;
		glm::vec3 getPos() const;
		bool hit(const HittableSprite& other) const;
		std::shared_ptr<Engine::HittableEntity> getEntity() const;
		std::shared_ptr<Engine::GraphicContext> getGraphicsContext() const;

		void activate();
		void deactivate();
		void updateX(float x);
		void updateY(float y);
		void moveBy(glm::vec3 delta);
		void updateEntity();
		void decreaseLifePoints();
		void setDirection(glm::vec3 direction);
		void updateProjectionMatrix(glm::mat4 matrix);
	private:
		static const std::string VERTEX_FILE;
		const static glm::vec3 OBJECT_CENTER;
		const static float OBJECT_RADIUS;
		const static float SCALE_MULTIPLIER;
		const static float SPEED;

		int life_points;
		glm::vec3 pos;
		glm::vec3 direction;
		bool is_active;
		std::shared_ptr<Engine::HittableEntity> entity;
		std::shared_ptr<Engine::GraphicContext> context;
	};
}