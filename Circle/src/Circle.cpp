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

std::shared_ptr<Engine::Entity> create_circle_obj(std::vector<glm::vec3>& vertices, std::vector<uint32_t>& indices) {
	auto vbo_obj = Engine::VertexBuffer::createStatic(vertices);
	auto vertex_vbo = std::make_shared<Engine::VertexBuffer>(std::move(vbo_obj));
	auto indices_vbo = std::make_shared<Engine::IndexBuffer>(indices.data(), indices.size());

	Engine::BufferLayout layout = {
		{ "Position", Engine::ShaderDataType::Float3 },
	};

	vertex_vbo->setLayout(layout);

	auto obj = Engine::Entity({ vertex_vbo }, indices_vbo, glm::mat4(), glm::mat4());

	return std::make_shared<Engine::Entity>(std::move(obj));
}

void generate_circle(float center_x, float center_y, float radius, int n_points, std::vector<glm::vec3>& vertices, std::vector<uint32_t>& indices) {
	vertices.emplace_back(center_x, center_y, 0);

	uint32_t idx = 0;
	float step = TWO_PI / n_points;
	for (float t = 0.0f; t < TWO_PI; t += step) {
		float x = cos(t) * radius;
		float y = sin(t) * radius;
		vertices.emplace_back(x, y, 0);

		idx++;
		if (idx >= 2) {
			indices.push_back(0);
			indices.push_back(idx - 1);
			indices.push_back(idx);
		}
	}

	// need to add the last triangle that connects the last point with the first one
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(idx);
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
	std::vector<uint32_t> indices;

	generate_circle(0, 0, 0.5, 50, vertices, indices);

	shader_program->bind();
	scene = Engine::Scene(shader_program, { create_circle_obj(vertices, indices) });

	Engine::RendererUtils::startMainLoop();
}
