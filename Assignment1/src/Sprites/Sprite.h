#pragma once

#include "Engine/engine.h"
#include <glm/glm.hpp>
#include <memory>

namespace Sprites {
	class Sprite {
	public:
		virtual bool isActive() const = 0;
		virtual float getX() const = 0;
		virtual float getY() const = 0;
		virtual void draw() const = 0;
		virtual glm::vec3 getPos() const = 0;
		virtual bool hit(const std::shared_ptr<Engine::HittableEntity>& other) const = 0;

		virtual void activate() = 0;
		virtual void deactivate() = 0;
		virtual void updateX(float delta_x) = 0;
		virtual void updateY(float delta_y) = 0;
		virtual void moveBy(glm::vec3 delta) = 0;
	};
};