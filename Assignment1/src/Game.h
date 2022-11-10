#pragma once

#include <vector>
#include "Sprites/Player.h"
#include "Sprites/Background.h"
#include "Sprites/Bullet.h"
#include "Sprites/Ghost.h"
#include "Sprites/Spore.h"
#include "Engine/engine.h"

class Game {
public:
	Game() {}
	Game(std::shared_ptr<Engine::Window> window);

	void draw();

	void shootBullet(float click_x, float click_y);
	void movePlayer();
	void rotatePlayer(float mouse_x, float mouse_y);
	void spawnGhost();
	void spawnSpore();
	void step();
private:
	static const float PLAYER_MOVE_DELTA;
	static const char* SPRITE_VERTEX_SHADER;
	static const char* SPRITE_FRAGMENT_SHADER;
	static const char* BACKGROUND_VERTEX_SHADER;
	static const char* BACKGROUND_FRAGMENT_SHADER;
	static const char* TEXT_VERTEX_SHADER;
	static const char* TEXT_FRAGMENT_SHADER;
	static const char* FONT_PATH;

	void updateEnemies();
	void updateBullets();
	void deleteInactiveSprites();
	void updateSpores();

	uint32_t score;
	Sprites::Player player;
	Sprites::Background background;
	std::vector<Sprites::Bullet> enemy_bullets;
	std::vector<Sprites::Bullet> player_bullets;
	std::shared_ptr<Engine::Window> window;
	std::vector<Sprites::Ghost> ghosts;
	std::vector<Sprites::Spore> spores;

	Engine::TextRenderer txt_renderer;
	std::shared_ptr<Engine::GraphicContext> sprite_ctx;
	std::shared_ptr<Engine::GraphicContext> background_ctx;
};
