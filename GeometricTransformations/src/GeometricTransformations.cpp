#include <iostream>
#include "Engine/src/Renderer/RendererUtils.h"
#include "Engine/src/Renderer/Shader/ShaderProgram.h"
#include "Engine/src/Renderer/Buffer/VertexBuffer.h"
#include "Engine/src/Renderer/Buffer/VertexArray.h"
#include "Engine/src/Renderer/Buffer/DataTypes.h"
#include "Engine/src/Exceptions/ShaderLoadException.h"

std::vector<float> vertices = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

uint32_t indices[] = {
	0, 1, 2, 1, 2, 3
};

Engine::ShaderProgram shader_program;

std::shared_ptr<Engine::VertexArray> vao;

void init_vao() {
	vao = std::make_shared<Engine::VertexArray>();
	auto vbo_obj = Engine::VertexBuffer::createStatic(vertices);
	auto vertex_vbo = std::make_shared<Engine::VertexBuffer>(std::move(vbo_obj));
	auto indices_vbo = std::make_shared<Engine::IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));

	Engine::BufferLayout layout = {
		{ "Position", Engine::ShaderDataType::Float3 },
		{ "Color", Engine::ShaderDataType::Float4 },
	};

	vertex_vbo->setLayout(layout);
	vao->setIndexBuffer(indices_vbo);
	vao->addVertexBuffer(vertex_vbo);
}

void drawScene() {
	Engine::RendererUtils::clear(Engine::ClearOptions::ColorBuffer);
	Engine::RendererUtils::drawIndexed(vao);
	Engine::RendererUtils::swapBuffers();
}

int main(int argc, char** argv)
{
	Engine::RendererUtils::init(argc, argv, 800, 800, 100, 100, "Triangolo");
	Engine::RendererUtils::setDisplayFunc(drawScene);
	Engine::RendererUtils::setClearColor(glm::vec4(0.0, 0.0, 0.0, 1.0));

	shader_program = Engine::ShaderProgram(
		"..\\GeometricTransformations\\shaders\\vertexShader.glsl",
		"..\\GeometricTransformations\\shaders\\fragmentShader.glsl"
	);

	shader_program.bind();
	init_vao();

	Engine::RendererUtils::startMainLoop();
}
