#include "Background.h"

namespace Sprites {
	Background::Background(std::shared_ptr<Engine::GraphicContext> context)
		: context(context)
	{
		auto window_options = context->getWindow()->getOptions();
		auto color = glm::vec4(1.0, 1.0, 1.0, 1.0);
		std::vector<glm::vec3> vertices = { glm::vec3(-1, -1, 0), glm::vec3(1, -1, 0), glm::vec3(1, 1, 0), glm::vec3(-1, 1, 0) };
		std::vector<uint32_t> indices = { 0, 1, 2, 0, 2, 3 };
		auto vbo_obj = Engine::VertexBuffer::createStatic(vertices);
		auto vertex_vbo = std::make_shared<Engine::VertexBuffer>(std::move(vbo_obj));
		auto vertex_array = std::make_shared<Engine::VertexArray>();

		vertex_vbo->setLayout({ { "Position", Engine::ShaderDataType::Float3 } });
		vertex_array->addVertexBuffer(vertex_vbo);

		auto idx_buff = std::make_shared<Engine::IndexBuffer>(indices);
		vertex_array->setIndexBuffer(idx_buff);
		vertex_array->setDrawSpecs({ { (uint32_t)indices.size(), Engine::DrawMode::Triangles } });

		entity = std::make_shared<Engine::Entity>(Engine::Entity::createEntity(vertex_array));

		entity->setProjectionMatrix(glm::ortho(0.0f, (float)window_options.width, 0.0f, (float)window_options.height));
		entity->getModelMatrixHandler()->scaleBy(glm::vec3(window_options.width / 2, window_options.height / 2, 0));
		entity->getModelMatrixHandler()->translateBy(glm::vec3(window_options.width / 2, window_options.height / 2, 0.0));
	}
	
	void Background::draw() const
	{
		context->getShaderProgram()->bind();
		auto time = Engine::RendererUtils::getElapsedTime() / 5000;
		auto options = context->getWindow()->getOptions();
		Engine::RendererUtils::uploadUniformFloat("time", time);
		Engine::RendererUtils::uploadUniformVec2("res", glm::vec2(options.width, options.height));
		entity->draw();
	}

	std::shared_ptr<Engine::GraphicContext> Background::getGraphicsContext() const
	{
		return context;
	}
}