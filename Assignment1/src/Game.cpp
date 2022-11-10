#pragma once

#include <numbers>
#include <algorithm>
#include <iostream>

#include "Game.h"
#include "Sprites/Ghost.h"
#include "Sprites/Spore.h"

const float Game::PLAYER_MOVE_DELTA = 10;
const char* Game::SPRITE_VERTEX_SHADER =		"..\\Assignment1\\res\\shaders\\sprites.vert";
const char* Game::SPRITE_FRAGMENT_SHADER =		"..\\Assignment1\\res\\shaders\\sprites.frag";
const char* Game::BACKGROUND_VERTEX_SHADER =	"..\\Assignment1\\res\\shaders\\background.vert";
const char* Game::BACKGROUND_FRAGMENT_SHADER =	"..\\Assignment1\\res\\shaders\\background.frag";
const char* Game::TEXT_VERTEX_SHADER =			"..\\Assignment1\\res\\shaders\\text.vert";
const char* Game::TEXT_FRAGMENT_SHADER =		"..\\Assignment1\\res\\shaders\\text.frag";
const char* Game::FONT_PATH =					"..\\Assignment1\\res\\fonts\\arial.ttf";

Game::Game(std::shared_ptr<Engine::Window> window)
	: window(window), score(0)
{
	const auto window_options = window->getOptions();

	auto sprite_shader = std::make_shared<Engine::ShaderProgram>(SPRITE_VERTEX_SHADER, SPRITE_FRAGMENT_SHADER);
	auto background_shader = std::make_shared<Engine::ShaderProgram>(BACKGROUND_VERTEX_SHADER, BACKGROUND_FRAGMENT_SHADER);
	sprite_ctx = std::make_shared<Engine::GraphicContext>(window, sprite_shader);
	background_ctx = std::make_shared<Engine::GraphicContext>(window, background_shader);

	background = Sprites::Background(background_ctx);
	player = Sprites::Player(glm::vec3(window_options.world_width / 2, window_options.world_height / 2, 0), sprite_ctx);
	auto txt_program = Engine::ShaderProgram(TEXT_VERTEX_SHADER, TEXT_FRAGMENT_SHADER);
	txt_renderer = Engine::TextRenderer(FONT_PATH, std::make_shared<Engine::ShaderProgram>(txt_program));
	txt_renderer.setProjectionMatrix(glm::ortho(0.0f, (float)window_options.world_width, 0.0f, (float)window_options.world_height));
}

void Game::draw()
{
	background_ctx->getShaderProgram()->bind();
	background.draw();
	background_ctx->getShaderProgram()->unbind();

	sprite_ctx->getShaderProgram()->bind();

	for (const auto& bullet : player_bullets) {
		if (bullet.isActive()) {
			bullet.draw();
		}
	}

	if (player.isActive()) {
		player.draw();
	}

	for (const auto& bullet : enemy_bullets) {
		if (bullet.isActive()) {
			bullet.draw();
		}
	}

	for (const auto& enemy : spores) {
		if (enemy.isActive()) {
			enemy.draw();
		}
	}

	for (const auto& enemy : ghosts) {
		if (enemy.isActive()) {
			enemy.draw();
		}
	}

	sprite_ctx->getShaderProgram()->unbind();
	auto proj = glm::ortho(0.0f, (float)window->getOptions().world_width, 0.0f, (float)window->getOptions().world_height);
	txt_renderer.setProjectionMatrix(proj);

	std::string status = "";
	if (!player.isActive()) {
		status += "GAMEOVER: ";
	}
	status += "SCORE " + std::to_string(score);
	txt_renderer.drawText(status, glm::vec4(0.5, 0.5, 0.5, 1.0), glm::vec3(0.0, 50.0, 0.0), glm::vec3(1.0));
}

void Game::shootBullet(float click_x, float click_y)
{
	if (!player.isActive())
		return;

	auto world_delta = glm::normalize(glm::vec3(click_x, click_y, 0) - player.getPos());
	auto pos = glm::vec3(player.getX(), player.getY(), 0);
	auto bullet = Sprites::Bullet(pos, world_delta, sprite_ctx, true);
	player_bullets.push_back(bullet);
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

	player.rotateBy(angle);
	player.updateEntity();
}

void Game::updateBullets()
{
	if (!player.isActive())
		return;

	auto options = window->getOptions();

	for (auto& bullet : player_bullets) {
		bullet.updateEntity();

		if (bullet.getX() < 0 || bullet.getX() > options.world_width || bullet.getY() < 0 || bullet.getY() > options.world_height) {
			bullet.deactivate();
		}
	}

	for (auto& bullet : enemy_bullets) {
		bullet.updateEntity();

		if (bullet.getX() < 0 || bullet.getX() > options.world_width || bullet.getY() < 0 || bullet.getY() > options.world_height) {
			bullet.deactivate();
		}
	}
}

void Game::updateEnemies()
{
	if (!player.isActive())
		return;

	auto update_enemy = [&](Sprites::HittableSprite& enemy) {
		if (!player.isActive()) {
			return;
		}
		
		auto hit = std::find_if(player_bullets.begin(), player_bullets.end(), [&](const Sprites::Bullet& b) {
			return b.isActive() && enemy.hit(b);
		});

		if (hit != player_bullets.end()) {
			hit->deactivate();
			enemy.decreaseLifePoints();
		}

		if (enemy.isActive() && enemy.hit(player)) {
			player.deactivate();
		}
	};

	std::for_each(ghosts.begin(), ghosts.end(), update_enemy);
	std::for_each(spores.begin(), spores.end(), update_enemy);
	std::for_each(enemy_bullets.begin(), enemy_bullets.end(), update_enemy);

	for (auto& enemy : ghosts) {
		if (!enemy.isActive())
			score++;

		auto dir = player.getPos() - enemy.getPos();
		enemy.setDirection(dir);
		enemy.updateEntity();
	}

	for (auto& enemy : spores) {
		if (!enemy.isActive())
			score++;

		enemy.updateEntity();
	}
}

void Game::deleteInactiveSprites()
{
	const auto is_inactive_checker = [](const Sprites::Sprite& s) { return !s.isActive(); };
	std::erase_if(player_bullets, is_inactive_checker);
	std::erase_if(enemy_bullets, is_inactive_checker);
	std::erase_if(spores, is_inactive_checker);
	std::erase_if(ghosts, is_inactive_checker);
}

void Game::updateSpores()
{
	for (auto& spore : spores) {
		if (!spore.shouldShot()) {
			continue;
		}

		auto delta = glm::normalize(player.getPos() - spore.getPos());
		auto pos = glm::vec3(spore.getX(), spore.getY(), 0);
		auto bullet = Sprites::Bullet(pos, delta, sprite_ctx, false);
		spore.updateShootTimeStamp();

		enemy_bullets.push_back(bullet);
	}
}

void Game::spawnGhost()
{
	if (!player.isActive())
		return;

	auto options = window->getOptions();
	int x, y;

	while (true) {
		x = rand() % options.world_width;
		y = rand() % options.world_height;
		const auto enemy = Sprites::Ghost(glm::vec3(x, y, 0), rand() % Sprites::Ghost::MAX_LEVEL + 1, sprite_ctx);

		if (!player.hit(enemy)) {
			ghosts.push_back(enemy);
			break;
		}
	}
}

void Game::spawnSpore()
{
	if (!player.isActive())
		return;

	auto options = window->getOptions();
	int x, y;

	while (true) {
		x = rand() % options.world_width;
		y = rand() % options.world_height;
		const auto enemy = Sprites::Spore(glm::vec3(x, y, 0), 1, sprite_ctx);

		if (!player.hit(enemy)) {
			spores.push_back(enemy);
			break;
		}
	}
}

void Game::step()
{
	updateSpores();
	updateBullets();
	updateEnemies();
	deleteInactiveSprites();
}
