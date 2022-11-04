#pragma once

#include "Sprite.h"
#include "Engine/engine.h"

namespace Sprites {
	class Spore : public HittableSprite {
	public:
		const static int MAX_LEVEL;

		Spore() : is_active(false) {}
		Spore(glm::vec3 pos, int life_points, std::shared_ptr<Engine::GraphicContext> context);

		bool isActive() const;
		float getX() const;
		float getY() const;
		void draw() const;
		glm::vec3 getPos() const;
		bool hit(const HittableSprite& other) const;
		std::shared_ptr<Engine::HittableEntity> getEntity() const;
		std::shared_ptr<Engine::GraphicContext> getGraphicsContext() const;
		bool shouldShot() const;

		void activate();
		void deactivate();
		void updateX(float x);
		void updateY(float y);
		void moveBy(glm::vec3 delta);
		void updateEntity();
		void decreaseLifePoints();
		void updateShootTimeStamp();
		void updateProjectionMatrix(glm::mat4 matrix);
	private:
		static const std::string VERTEX_FILE;
		const static glm::vec3 OBJECT_CENTER;
		const static float OBJECT_RADIUS;
		const static float SHOOT_DELAY;
		const static float SPEED;

		float last_shot_timestamp;
		int life_points;
		glm::vec3 pos;
		bool is_active;
		std::shared_ptr<Engine::HittableEntity> entity;
		std::shared_ptr<Engine::GraphicContext> context;
	};
}