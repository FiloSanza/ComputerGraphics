#include <iostream>
#include "Engine/src/Renderer/RendererUtils.h"
#include "Engine/src/Renderer/Shader/ShaderProgram.h"
#include "Engine/src/Renderer/Buffer/VertexBuffer.h"
#include "Engine/src/Renderer/Buffer/VertexArray.h"
#include "Engine/src/Renderer/Buffer/DataTypes.h"
#include "Engine/src/Exceptions/ShaderLoadException.h"

const float PI = 3.14159265359;
const float TWO_PI = 2 * PI;

std::shared_ptr<Engine::VertexArray> vao;

void init_vao(std::vector<float>& vertices, std::vector<uint32_t>& indices) {
	vao = std::make_shared<Engine::VertexArray>();
	auto vbo_obj = Engine::VertexBuffer::createStatic(vertices);
	auto vertex_vbo = std::make_shared<Engine::VertexBuffer>(std::move(vbo_obj));
	auto indices_vbo = std::make_shared<Engine::IndexBuffer>(indices.data(), indices.size());

	Engine::BufferLayout layout = {
		{ "Position", Engine::ShaderDataType::Float3 },
		//{ "Color", Engine::ShaderDataType::Float4 },
	};

	vertex_vbo->setLayout(layout);
	vao->setIndexBuffer(indices_vbo);
	vao->addVertexBuffer(vertex_vbo);
}

void generate_circle(float center_x, float center_y, float radius, int n_points, std::vector<float>& vertices, std::vector<uint32_t>& indices) {
	vertices.push_back(center_x);
	vertices.push_back(center_y);
	vertices.push_back(0);				// z

	uint32_t idx = 0;
	float step = TWO_PI / n_points;
	for (float t = 0.0f; t < TWO_PI; t += step) {
		float x = cos(t) * radius;
		float y = sin(t) * radius;
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0);			// z

		idx++;
		if (idx >= 2) {
			indices.push_back(0);		// center
			indices.push_back(idx - 1);	// previous point
			indices.push_back(idx);		// last point created
		}
	}

	// need to add the last triangle that connects the last point with the first one
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(idx);
}

void drawScene() {
	Engine::RendererUtils::clear(Engine::ClearOptions::ColorBuffer);
	Engine::RendererUtils::setPolygonModeDebug();
	Engine::RendererUtils::drawIndexed(vao);
	Engine::RendererUtils::swapBuffers();
}

int main(int argc, char** argv)
{
	Engine::RendererUtils::init(argc, argv, 800, 800, 100, 100, "Circle");
	Engine::RendererUtils::setDisplayFunc(drawScene);
	Engine::RendererUtils::setClearColor(glm::vec4(0.0, 0.0, 0.0, 1.0));

	auto shader_program = Engine::ShaderProgram(
		"..\\Circle\\shaders\\vertexShader.glsl",
		"..\\Circle\\shaders\\fragmentShader.glsl"
	);

	std::vector<float> vertices;
	std::vector<uint32_t> indices;

	generate_circle(0, 0, 0.5, 50, vertices, indices);

	shader_program.bind();
	init_vao(vertices, indices);

	Engine::RendererUtils::startMainLoop();
}
