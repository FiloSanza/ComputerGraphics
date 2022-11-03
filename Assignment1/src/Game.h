#pragma once

#include <vector>
#include "Sprites/Player.h"
#include "Sprites/Background.h"
#include "Sprites/Ghost.h"
#include "Sprites/Bullet.h"
#include "Engine/engine.h"

class Game {
public:
	Game() {}
	Game(std::shared_ptr<Engine::Window> window);

	void draw() const;

	void shootBullet(float click_x, float click_y);
	void movePlayer();
	void rotatePlayer(float mouse_x, float mouse_y);
	void spawnGhost();
	void step();
private:
	static const float PLAYER_MOVE_DELTA;
	static const char* SPRITE_VERTEX_SHADER;
	static const char* SPRITE_FRAGMENT_SHADER;
	static const char* BACKGROUND_VERTEX_SHADER;
	static const char* BACKGROUND_FRAGMENT_SHADER;

	void updateGhosts();
	void updateBullets();
	void deleteInactiveSprites();

	Sprites::Player player;
	Sprites::Background background;
	std::vector<Sprites::Ghost> ghosts;
	std::vector<Sprites::Bullet> bullets;
	std::shared_ptr<Engine::Window> window;
	std::shared_ptr<Engine::GraphicContext> sprite_ctx;
	std::shared_ptr<Engine::GraphicContext> background_ctx;
};
