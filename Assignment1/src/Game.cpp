#pragma once

#include <numbers>
#include <iostream>

#include "Game.h"

const float Game::PLAYER_MOVE_DELTA = 10;
const char* Game::SPRITE_VERTEX_SHADER = "..\\Assignment1\\res\\shaders\\sprites.vert";
const char* Game::SPRITE_FRAGMENT_SHADER = "..\\Assignment1\\res\\shaders\\sprites.frag";
const char* Game::BACKGROUND_VERTEX_SHADER = "..\\Assignment1\\res\\shaders\\background.vert";
const char* Game::BACKGROUND_FRAGMENT_SHADER = "..\\Assignment1\\res\\shaders\\background.frag";

Game::Game(std::shared_ptr<Engine::Window> window)
	: window(window)
{
	const auto window_options = window->getOptions();

	auto sprite_shader = std::make_shared<Engine::ShaderProgram>(SPRITE_VERTEX_SHADER, SPRITE_FRAGMENT_SHADER);
	auto background_shader = std::make_shared<Engine::ShaderProgram>(BACKGROUND_VERTEX_SHADER, BACKGROUND_FRAGMENT_SHADER);
	sprite_ctx = std::make_shared<Engine::GraphicContext>(window, sprite_shader);
	background_ctx = std::make_shared<Engine::GraphicContext>(window, background_shader);

	background = Sprites::Background(background_ctx);
	player = Sprites::Player(glm::vec3(window_options.world_width / 2, window_options.world_height / 2, 0), sprite_ctx);
}

void Game::draw() const
{
	background_ctx->getShaderProgram()->bind();
	background.draw();
	background_ctx->getShaderProgram()->unbind();

	sprite_ctx->getShaderProgram()->bind();

	for (const auto& bullet : bullets) {
		if (bullet.isActive()) {
			bullet.draw();
		}
	}

	if (player.isActive()) {
		player.draw();
	}

	for (const auto& ghost : ghosts) {
		if (ghost.isActive()) {
			ghost.draw();
		}
	}

	sprite_ctx->getShaderProgram()->unbind();
}

void Game::shootBullet(float click_x, float click_y)
{
	if (!player.isActive())
		return;

	auto screen_click = window->convertWorldToWindowCoordinates({ click_x, click_y, 0 });
	auto screen_player = window->convertWorldToWindowCoordinates({ player.getX(), player.getY(), 0 });

	auto screen_delta = glm::normalize(screen_click - screen_player);
	auto world_delta = glm::normalize(glm::vec3(click_x, click_y, 0) - player.getPos());

	auto pos = glm::vec3(player.getX(), player.getY(), 0);
	auto bullet = Sprites::Bullet(pos, world_delta, sprite_ctx);
	bullets.push_back(bullet);
}

void Game::movePlayer()
{
	if (!player.isActive())
		return;

	auto options = window->getOptions();

	glm::vec3 delta(0);
	if (window->isKeyPressed(Engine::Keyboard::Key::A) && player.getX() - PLAYER_MOVE_DELTA >= 0) {
		delta.x -= PLAYER_MOVE_DELTA;
	}

	if (window->isKeyPressed(Engine::Keyboard::Key::S) && player.getY() - PLAYER_MOVE_DELTA >= 0) {
		delta.y -= PLAYER_MOVE_DELTA;
	}

	if (window->isKeyPressed(Engine::Keyboard::Key::D) && player.getX() + PLAYER_MOVE_DELTA < options.world_width) {
		delta.x += PLAYER_MOVE_DELTA;
	}

	if (window->isKeyPressed(Engine::Keyboard::Key::W) && player.getY() + PLAYER_MOVE_DELTA < options.world_height) {
		delta.y += PLAYER_MOVE_DELTA;
	}
	player.moveBy(delta);
	player.updateEntity();
}
	
void Game::rotatePlayer(float mouse_x, float mouse_y)
{
	if (!player.isActive())
		return;

	auto angle = atan2(mouse_y - player.getY(), mouse_x - player.getX()) * 180.0 / std::numbers::pi;

	//std::cout << angle << " - [" << mouse_x << ", " << mouse_y << "]\n";

	player.rotateBy(angle);
	player.updateEntity();
}

void Game::updateBullets()
{
	if (!player.isActive())
		return;

	auto options = window->getOptions();

	for (auto& bullet : bullets) {
		bullet.updateEntity();

		if (bullet.getX() < 0 || bullet.getX() > options.world_width || bullet.getY() < 0 || bullet.getY() > options.world_height) {
			bullet.deactivate();
		}
	}
}

void Game::updateGhosts()
{
	if (!player.isActive())
		return;

	for (auto& ghost : ghosts) {
		auto hit = std::find_if(bullets.begin(), bullets.end(), [&](const Sprites::Bullet& b) {
			return ghost.hit(b);
		});

		if (hit != bullets.end()) {
			hit->deactivate();
			ghost.decreaseLifePoints();
		}

		/*if (ghost.hit(player)) {
			player.deactivate();
			break;
		}*/

		auto dir = player.getPos() - ghost.getPos();
		ghost.setDirection(dir);
		ghost.updateEntity();
	}
}

void Game::deleteInactiveSprites()
{
	const auto is_inactive_checker = [](const Sprites::Sprite& s) { return !s.isActive(); };
	std::erase_if(bullets, is_inactive_checker);
	std::erase_if(ghosts, is_inactive_checker);
}

void Game::spawnGhost()
{
	if (!player.isActive())
		return;

	auto options = window->getOptions();
	int x, y;

	Sprites::Ghost ghost;

	do {
		x = rand() % options.world_width;
		y = rand() % options.world_height;
		ghost = Sprites::Ghost(glm::vec3(x, y, 0), rand() % Sprites::Ghost::MAX_LEVEL + 1, sprite_ctx);
	} while (player.hit(ghost));

	ghosts.push_back(ghost);
}

void Game::step()
{
	updateBullets();
	updateGhosts();
	deleteInactiveSprites();
}
