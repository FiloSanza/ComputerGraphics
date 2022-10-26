#include <iostream>
#include <algorithm>
#include <ranges>
#include "Engine/engine.h"

const float PI = 3.14159265359f;
const float TWO_PI = 2 * PI;
const int width = 1600;
const int height = 800;

struct User {
	int x = 0;
	int y = 0;
	double angle = 0.0;
	std::shared_ptr<Engine::HittableEntity> entity;
};

struct Bullet {
	float x = 0;
	float y = 0;
	float delta_x = 0;
	float delta_y = 0;
	std::shared_ptr<Engine::HittableEntity> entity;
};

struct Scene {
	User user;
	std::vector<Bullet> bullets;
	std::shared_ptr<Engine::HittableEntity> background;


	void draw() {
		background->draw();
		user.entity->draw();
		std::for_each(bullets.begin(), bullets.end(), [](const auto& b) { 
			b.entity->draw(); 
		});
	}

	void update_user_entity() {
		const auto proj_matrix = user.entity->getModelMatrixHandler();
		proj_matrix->translateBy(glm::vec3(width / 2 + user.x, height / 2 + user.y, 0.0));
		proj_matrix->scaleBy(glm::vec3(100.0, 100.0, 1.0));
		proj_matrix->rotate(user.angle);
		Engine::RendererUtils::updateWindow();
	}

	void update_bullets() {
		std::vector<Bullet> active_bullets;

		std::ranges::copy_if(bullets, std::back_inserter(active_bullets), [&](Bullet b) {
			return b.entity->hit(background);
		});

		bullets.swap(active_bullets);

		for (auto& bullet : bullets) {
			auto model_mat = bullet.entity->getModelMatrixHandler();
			bullet.x += bullet.delta_x * 10;
			bullet.y += bullet.delta_y * 10;
			model_mat->translateBy(glm::vec3(bullet.x, bullet.y, 0));
		}

		std::cerr << "ACTIVE BULLETS: " << bullets.size() << "\n";
	}
};


std::shared_ptr<Engine::ShaderProgram> shader_program;
Scene scene;
std::shared_ptr<Engine::Window> window;

std::shared_ptr<Engine::HittableEntity> create_bullet(float center_x, float center_y, float radius, int n_points) {	
	auto color = glm::vec4(1, 0, 0, 1.0);
	std::vector<Engine::Vertex> vertices;
	vertices.push_back({ glm::vec3(center_x, center_y, 0), color });

	float step = TWO_PI / n_points;
	for (int i = 0; i <= n_points; i++) {
		const float t = step * i;
		const float x = cos(t) * radius + center_x;
		const float y = sin(t) * radius + center_y;
		vertices.push_back({ glm::vec3(x, y, 0), color });
	}

	auto vbo_obj = Engine::VertexBuffer::createStatic(vertices);
	auto vertex_vbo = std::make_shared<Engine::VertexBuffer>(std::move(vbo_obj));
	auto vertex_array = std::make_shared<Engine::VertexArray>();

	vertex_vbo->setLayout({
		{ "Position", Engine::ShaderDataType::Float3 },
		{ "Color", Engine::ShaderDataType::Float4 },
	});
	vertex_array->addVertexBuffer(vertex_vbo);
	vertex_array->setDrawSpecs({
		{ (uint32_t)vertices.size(), Engine::DrawMode::TriangleFan },
	});

	auto obj = Engine::Entity::createEntity(vertex_array);
	return std::make_shared<Engine::HittableEntity>(obj);
}

std::shared_ptr<Engine::VertexArray> create_user(float center_x, float center_y, float radius, int n_points) {
	auto color = glm::vec4(0, 0, 1, 1.0);
	std::vector<Engine::Vertex> vertices;
	vertices.push_back({ glm::vec3(center_x, center_y, 0), color });

	float step = TWO_PI / n_points;
	for (int i = 0; i <= n_points; i++) {
		const float t = step * i;
		const float x = cos(t) * radius;
		const float y = sin(t) * radius;
		vertices.push_back({ glm::vec3(x, y, 0), color });
	}

	int circle_size = vertices.size();

	vertices.push_back({ glm::vec3(1.4,  0.5, 0.0), color });
	vertices.push_back({ glm::vec3(1.4, -0.5, 0.0), color });
	vertices.push_back({ glm::vec3(   0,   0, 0.0), color });

	auto vbo_obj = Engine::VertexBuffer::createStatic(vertices);
	auto vertex_vbo = std::make_shared<Engine::VertexBuffer>(std::move(vbo_obj));
	auto vertex_array = std::make_shared<Engine::VertexArray>();

	vertex_vbo->setLayout({ 
		{ "Position", Engine::ShaderDataType::Float3 },
		{ "Color", Engine::ShaderDataType::Float4 },
	});
	vertex_array->addVertexBuffer(vertex_vbo);
	vertex_array->setDrawSpecs({ 
		{ (uint32_t)circle_size, Engine::DrawMode::TriangleFan },
		{ (uint32_t)vertices.size() - circle_size, Engine::DrawMode::Triangles }
	});

	return vertex_array;
}

std::shared_ptr<Engine::HittableEntity> generate_user(float center_x, float center_y, float radius, int n_points) {
	auto vao = create_user(center_x, center_y, radius, n_points);
	auto obj = Engine::HittableEntity::createEntity(vao);
	return std::make_shared<Engine::HittableEntity>(obj);
}


void drawScene() {
	Engine::RendererUtils::clear(Engine::ClearOptions::ColorBuffer);
	//Engine::RendererUtils::draw(vertex_array);
	scene.draw();
	Engine::RendererUtils::swapBuffers();
}

void update_user_position(int value) {
	if (window->isKeyPressed(Engine::Keyboard::Key::A)) {
		scene.user.x -= 10;
	}

	if (window->isKeyPressed(Engine::Keyboard::Key::S)) {
		scene.user.y -= 10;
	}

	if (window->isKeyPressed(Engine::Keyboard::Key::D)) {
		scene.user.x += 10;
	}

	if (window->isKeyPressed(Engine::Keyboard::Key::W)) {
		scene.user.y += 10;
	}

	scene.update_user_entity();
	Engine::RendererUtils::addTimerCallback(update_user_position, 25, 0);
}

void update_bullets(int value) {
	scene.update_bullets();
	Engine::RendererUtils::updateWindow();
	Engine::RendererUtils::addTimerCallback(update_bullets, 25, 0);
}

int main(int argc, char** argv)
{
	Engine::RendererUtils::init(argc, argv);
	Engine::WindowOptions options;
	options.width = width;
	options.height = height;
	options.title = "Assignment 1";
	options.enableEvent(Engine::WindowEvent::KeyPress);
	options.enableEvent(Engine::WindowEvent::MouseMovement);
	options.enableEvent(Engine::WindowEvent::MouseClick);
	window = std::make_shared<Engine::Window>(options);
	Engine::RendererUtils::setDisplayFunc(drawScene);
	Engine::RendererUtils::setClearColor(glm::vec4(1.0, 0.0, 1.0, 1.0));

	shader_program = std::make_shared<Engine::ShaderProgram>(
		"..\\Assignment1\\shaders\\vertexShader.glsl",
		"..\\Assignment1\\shaders\\fragmentShader.glsl"
	);

	Engine::EventsDispatcher::getInstance().registerCallback(Engine::EventType::MouseMoved, [&](const Engine::Event& evt) {
		auto x = evt.getMouseX() - width / 2.0 - scene.user.x;
		auto y = height / 2 - evt.getMouseY() - scene.user.y;
		auto angle = atan2(y, x) * 180.0 / PI;
		scene.user.angle = angle;

		scene.update_user_entity();
	});

	Engine::EventsDispatcher::getInstance().registerCallback(Engine::EventType::MouseClick, [&](const Engine::Event& evt) {
		if (evt.getMouseButton() != Engine::Mouse::Button::Left) {
			return;
		}

		auto click_x = evt.getMouseX() - width / 2.0;
		auto click_y = height / 2.0 - evt.getMouseY();
		auto delta = glm::normalize(glm::vec3(click_x - scene.user.x, click_y - scene.user.y, 0));

		auto bullet_ent = create_bullet(0, 0, 1, 4);
		bullet_ent->setProjectionMatrix(glm::ortho(0.0f, (float)width, 0.0f, (float)height));
		bullet_ent->getModelMatrixHandler()->scaleBy(glm::vec3(20, 20, 0));
		scene.bullets.push_back({ scene.user.x + width / 2.0f, scene.user.y + height / 2.0f, delta.x, delta.y, bullet_ent });
	});
	
	scene.user.entity = generate_user(0, 0, 1, 100);
	scene.user.entity->setProjectionMatrix(glm::ortho(0.0f, (float)width, 0.0f, (float)height));

	shader_program->bind();
	scene.update_user_entity();

	Engine::RendererUtils::addTimerCallback(update_user_position, 25, 0);
	Engine::RendererUtils::addTimerCallback(update_bullets, 25, 0);
	Engine::RendererUtils::startMainLoop();
}
