#pragma once

#include "Sprite.h"

namespace Sprites {
	class Bullet : public HittableSprite {
	public:
		Bullet() : is_active(false) {}
		Bullet(glm::vec3 pos, glm::vec3 direction, std::shared_ptr<Engine::GraphicContext> context, bool is_player_bullet);

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
		void updateEntity();
		void setDirecton(glm::vec3 direction);
		void updateProjectionMatrix(glm::mat4 matrix);
		void decreaseLifePoints();
	private:
		const static glm::vec4 PLAYER_BULLET_COLOR;
		const static glm::vec4 ENEMY_BULLET_COLOR;
		const static glm::vec3 OBJECT_CENTER;
		const static float OBJECT_RADIUS;
		const static float PLAYER_BULLET_SPEED;
		const static float ENEMY_BULLET_SPEED;

		int life_points;
		glm::vec3 pos;
		glm::vec3 direction;
		bool is_active;
		bool is_player_bullet;
		std::shared_ptr<Engine::GraphicContext> context;
		std::shared_ptr<Engine::HittableEntity> entity;
	};

}