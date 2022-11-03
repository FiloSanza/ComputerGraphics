#pragma once

#include "Sprite.h"

namespace Sprites {
	class Background : public Sprite {
	public:
		Background() {}
		Background(std::shared_ptr<Engine::GraphicContext> context);
		bool isActive() const { return true; }
		float getX() const { return 0; }
		float getY() const { return 0; }
		glm::vec3 getPos() const { return glm::vec3(0); }
		bool hit(const Sprite& other) const { return false; }
		void draw() const;
		std::shared_ptr<Engine::GraphicContext> getGraphicsContext() const;

		void activate() {}
		void deactivate() {}
		void updateX(float delta_x) {}
		void updateY(float delta_y) {}
		void moveBy(glm::vec3 delta) {}
		void updateEntity() {}
	private:
		const static glm::vec3 OBJECT_CENTER;
		const static float OBJECT_RADIUS;

		std::shared_ptr<Engine::Entity> entity;
		std::shared_ptr<Engine::GraphicContext> context;
	};
}