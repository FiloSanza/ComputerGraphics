#pragma once

#include "Sprite.h"

namespace Sprites {
	class Player : public HittableSprite {
	public:
		Player() : is_active(false) {}
		Player(glm::vec3 pos, std::shared_ptr<Engine::GraphicContext> context);
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
		void updateX(float delta_x);
		void updateY(float delta_y);
		void moveBy(glm::vec3 delta);
		void rotateBy(float angle);
		void updateEntity();
		void updateProjectionMatrix(glm::mat4 matrix);
	private:
		const static glm::vec3 OBJECT_CENTER;
		const static float OBJECT_RADIUS;

		glm::vec3 pos;
		glm::vec3 screen_pos;
		float angle;
		bool is_active;
		std::shared_ptr<Engine::HittableEntity> entity;
		std::shared_ptr<Engine::GraphicContext> context;
	};
}