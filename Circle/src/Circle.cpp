#include <iostream>
#include "Engine/src/Renderer/RendererUtils.h"
#include "Engine/src/Renderer/Shader/ShaderProgram.h"
#include "Engine/src/Renderer/Buffer/VertexBuffer.h"
#include "Engine/src/Renderer/Buffer/VertexArray.h"
#include "Engine/src/Renderer/Buffer/DataTypes.h"
#include "Engine/src/Exceptions/ShaderLoadException.h"
#include "Engine/src/Renderer/Scene/Entity.h"
#include "Engine/src/Renderer/Scene/Scene.h"
#include "Engine/src/Utils/Window.h"

const float PI = 3.14159265359f;
const float TWO_PI = 2 * PI;

std::vector<Engine::Entity> objects;
std::shared_ptr<Engine::ShaderProgram> shader_program;
Engine::Scene scene;

std::shared_ptr<Engine::Entity> create_circle_obj(std::vector<glm::vec3>& vertices) {
	auto vbo_obj = Engine::VertexBuffer::createStatic(vertices);
	auto vertex_vbo = std::make_shared<Engine::VertexBuffer>(std::move(vbo_obj));

	vertex_vbo->setLayout({ { "Position", Engine::ShaderDataType::Float3 } });
	auto obj = Engine::Entity::createEntity({ vertex_vbo }, vertices.size(), Engine::DrawMode::TriangleFan);
	return std::make_shared<Engine::Entity>(std::move(obj));
}

void generate_circle(float center_x, float center_y, float radius, int n_points, std::vector<glm::vec3>& vertices) {
	vertices.emplace_back(center_x, center_y, 0);

	float step = TWO_PI / n_points;
	for (int i = 0; i <= n_points; i++) {
		const float t = step * i;
		const float x = cos(t) * radius;
		const float y = sin(t) * radius;
		vertices.emplace_back(x, y, 0);
	}
}

void drawScene() {
	Engine::RendererUtils::clear(Engine::ClearOptions::ColorBuffer);
	scene.draw();
	Engine::RendererUtils::swapBuffers();
}

int main(int argc, char** argv)
{
	Engine::RendererUtils::init(argc, argv);
	Engine::WindowOptions options;
	options.height = 800;
	options.width = 800;
	options.title = "Circle";
	Engine::Window window(options);
	Engine::RendererUtils::setDisplayFunc(drawScene);
	Engine::RendererUtils::setClearColor(glm::vec4(0.0, 0.0, 0.0, 1.0));

	shader_program = std::make_shared<Engine::ShaderProgram>(
		"..\\Circle\\shaders\\vertexShader.glsl",
		"..\\Circle\\shaders\\fragmentShader.glsl"
	);

	std::vector<glm::vec3> vertices;

	generate_circle(0, 0, 0.5, 50, vertices);

	shader_program->bind();
	scene = Engine::Scene(shader_program, { create_circle_obj(vertices) });

	Engine::RendererUtils::startMainLoop();
}
