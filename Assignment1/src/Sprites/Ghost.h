#pragma once

#include "Sprite.h"
#include "Engine/engine.h"
#include <memory>
#include <string>

namespace Sprites {
	class Ghost : public Sprite {
	public:
		Ghost() {}
		Ghost(float screen_width, float screen_height);

		bool isActive() const;
		float getX() const;
		float getY() const;
		void draw() const;
		glm::vec3 getPos() const;
		bool hit(const std::shared_ptr<Engine::HittableEntity>& other) const;

		void activate();
		void deactivate();
		void updateX(float x);
		void updateY(float y);
		void moveBy(glm::vec3 delta);
	private:
		static const std::string VERTEX_FILE;

		glm::vec3 pos;
		bool is_active;
		std::shared_ptr<Engine::HittableEntity> entity;
	};
}