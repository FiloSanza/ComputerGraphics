#include <iostream>
#include <algorithm>
#include <ranges>
#include <numbers>
#include "Game.h"

constexpr int SPAWN_ENEMY_DELAY = 3000;
constexpr int STEP_DELAY = 25;
constexpr int INITIAL_WIDTH = 1200;
constexpr int INITIAL_HEIGHT = 600;

Game game;
std::shared_ptr<Engine::Window> window;

void drawScene() {
	Engine::RendererUtils::clear(Engine::ClearOptions::ColorBuffer);

	if (window->isKeyPressed(Engine::Keyboard::Key::P)) {
		Engine::RendererUtils::enableDebugMode();
	}
	else {
		Engine::RendererUtils::disableDebugMode();
	}

	game.draw();
	Engine::RendererUtils::swapBuffers();
}

void spawn_ghost(int value) {
	game.spawnGhost();
	Engine::RendererUtils::addTimerCallback(spawn_ghost, SPAWN_ENEMY_DELAY, 0);
}

void spawn_spore(int value) {
	game.spawnSpore();
	Engine::RendererUtils::addTimerCallback(spawn_spore, SPAWN_ENEMY_DELAY, 0);
}

void step(int value) {
	game.movePlayer();
	game.step();
	Engine::RendererUtils::updateWindow();
	Engine::RendererUtils::addTimerCallback(step, STEP_DELAY, 0);
}

int main(int argc, char** argv)
{
	Engine::RendererUtils::init(argc, argv);
	Engine::WindowOptions options;
	options.width = INITIAL_WIDTH;
	options.height = INITIAL_HEIGHT;
	options.world_width = INITIAL_WIDTH;
	options.world_height = INITIAL_HEIGHT;
	options.title = "Assignment 1";
	options.enableEvent(Engine::WindowEvent::AllEnabled);
	window = std::make_shared<Engine::Window>(options);
	Engine::RendererUtils::setDisplayFunc(drawScene);
	Engine::RendererUtils::setClearColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	game = Game(window);

	Engine::EventsDispatcher::getInstance().registerCallback(Engine::EventType::MouseMoved, [&](const Engine::Event& evt) {
		auto x = evt.getMouseX();
		auto y = window->getOptions().height - evt.getMouseY();
		auto world_coord = window->convertWindowToWorldCoordinates({ x, y, 0.0 });
		
		game.rotatePlayer(world_coord.x, world_coord.y);
	});

	Engine::EventsDispatcher::getInstance().registerCallback(Engine::EventType::MouseClick, [&](const Engine::Event& evt) {
		if (evt.getMouseButton() != Engine::Mouse::Button::Left) {
			return;
		}

		auto click_x = evt.getMouseX();
		auto click_y = window->getOptions().height - evt.getMouseY();
		auto world_coord = window->convertWindowToWorldCoordinates({ click_x, click_y, 0.0 });

		game.shootBullet(world_coord.x, world_coord.y);
	});
	
	Engine::RendererUtils::enableBlend();

	Engine::RendererUtils::addTimerCallback(spawn_ghost, SPAWN_ENEMY_DELAY, 0);
	Engine::RendererUtils::addTimerCallback(spawn_spore, SPAWN_ENEMY_DELAY + SPAWN_ENEMY_DELAY / 2, 0);
	Engine::RendererUtils::addTimerCallback(step, STEP_DELAY, 0);
	Engine::RendererUtils::startMainLoop();
}
