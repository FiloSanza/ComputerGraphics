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
#include "Engine/src/Events/EventsDispatcher.h"
#include "Engine/src/Events/Event.h"

const float PI = 3.14159265359f;
const float TWO_PI = 2 * PI;

std::shared_ptr<Engine::ShaderProgram> shader_program;
Engine::Scene scene;

void drawScene() {
	Engine::RendererUtils::clear(Engine::ClearOptions::ColorBuffer);
	//Engine::RendererUtils::setPolygonModeDebug();
	scene.draw();
	Engine::RendererUtils::swapBuffers();
}

std::shared_ptr<Engine::Entity> create_scene_object(const std::vector<float>& vertices, const std::vector<uint32_t> indices) {
	auto vbo_obj = Engine::VertexBuffer::createStatic(vertices);
	auto vertex_vbo = std::make_shared<Engine::VertexBuffer>(std::move(vbo_obj));
	auto indices_vbo = std::make_shared<Engine::IndexBuffer>(indices.data(), indices.size());

	Engine::BufferLayout layout = {
		{ "Position", Engine::ShaderDataType::Float3 },
		{ "Color", Engine::ShaderDataType::Float4 },
	};

	vertex_vbo->setLayout(layout);
	auto obj = Engine::Entity({ vertex_vbo }, indices_vbo, glm::mat4(), glm::mat4());
	return std::make_shared<Engine::Entity>(obj);
}

void push_glm_vertex_to_vector(std::vector<float>& vec, const glm::vec3 coord, const glm::vec4 color) {
	vec.push_back(coord.x);
	vec.push_back(coord.y);
	vec.push_back(coord.z);
	vec.push_back(color.r);
	vec.push_back(color.g);
	vec.push_back(color.b);
	vec.push_back(color.a);
}

std::shared_ptr<Engine::Entity> create_rectangle(glm::vec3 top_left, glm::vec3 top_right, glm::vec3 bottom_right, glm::vec3 bottom_left, glm::vec4 color) {
	std::vector<float> vertices = {};
	push_glm_vertex_to_vector(vertices, top_left, color);
	push_glm_vertex_to_vector(vertices, top_right, color);
	push_glm_vertex_to_vector(vertices, bottom_right, color);
	push_glm_vertex_to_vector(vertices, bottom_left, color);
	std::vector<uint32_t> indices = { 0, 1, 2, 0, 2, 3 };
	return create_scene_object(vertices, indices);
}

std::shared_ptr<Engine::Entity> create_circle(glm::vec3 center, float radius, int n_vertices, glm::vec4 color, float depth) {
	std::vector<float> vertices;
	std::vector<uint32_t> indices;
	push_glm_vertex_to_vector(vertices, center, color);

	uint32_t idx = 1;
	float step = TWO_PI / n_vertices;
	for (float t = 0; t < TWO_PI; t += step) {
		push_glm_vertex_to_vector(
			vertices, 
			glm::vec3(center.x + cos(t) * radius, center.y + sin(t) * radius, depth), 
			color
		);
		idx++;
		if (idx >= 3) {
			size_t size = vertices.size();
			indices.push_back(0);
			indices.push_back(idx - 2);
			indices.push_back(idx - 1);
		}
	}

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(idx - 1);

	return create_scene_object(vertices, indices);
}

std::shared_ptr<Engine::Entity> create_moutains(float start, float end, float height, float depth, float frequency, glm::vec4 color, uint32_t steps) {
	float delta_x = (end - start) / steps;
	float delta_angle = TWO_PI / steps;
	std::vector<float> vertices;
	std::vector<uint32_t> indices;

	uint32_t idx = 0;
	for (float x = start, angle = 0; x <= end; x+=delta_x, angle+=delta_angle) {
		push_glm_vertex_to_vector(vertices, glm::vec3(x, 0, depth), color);
		push_glm_vertex_to_vector(vertices, glm::vec3(x, abs(sin(angle * frequency) * height), depth), color);
		idx += 2;

		if (idx > 3) {
			indices.push_back(idx - 4);
			indices.push_back(idx - 3);
			indices.push_back(idx - 2);
			indices.push_back(idx - 3);
			indices.push_back(idx - 2);
			indices.push_back(idx - 1);
		}
	}

	return create_scene_object(vertices, indices);
}

int main(int argc, char** argv)
{
	Engine::RendererUtils::init(argc, argv);
	Engine::WindowOptions options;
	options.title = "ExampleScene";
	options.height = 800;
	options.width = 800;
	options.enableEvent(Engine::WindowEvent::KeyPress);
	options.enableEvent(Engine::WindowEvent::MouseClick);
	options.enableEvent(Engine::WindowEvent::MouseMovement);
	Engine::Window window(options);
	Engine::RendererUtils::setDisplayFunc(drawScene);
	Engine::RendererUtils::setClearColor(glm::vec4(0.0, 0.0, 0.0, 1.0));
	Engine::RendererUtils::enableBlend();

	Engine::EventsDispatcher::getInstance().registerCallback(Engine::EventType::KeyPressed, [](const Engine::Event& evt) {
		std::cout << "Key '" << (unsigned char)evt.getKey() << "' pressed\n";
	});

	Engine::EventsDispatcher::getInstance().registerCallback(Engine::EventType::MouseClick, [](const Engine::Event& evt) {
		std::cout << "Key " 
			<< Engine::Mouse::mouseButtonToString(evt.getMouseButton())  
			<< " is " 
			<< Engine::Mouse::mouseButtonStateToString(evt.getMouseButtonState()) 
			<< "\n";
	});

	Engine::EventsDispatcher::getInstance().registerCallback(Engine::EventType::MouseMoved, [](const Engine::Event& evt) {
		std::cout << "Mouse at: {" << evt.getMouseX() << ", " << evt.getMouseY() << "}\n";
	});

	shader_program = std::make_shared<Engine::ShaderProgram>(
		"..\\ExampleScene\\shaders\\vertexShader.glsl",
		"..\\ExampleScene\\shaders\\fragmentShader.glsl"
		);

	scene = Engine::Scene(shader_program);

	// sky
	scene.addObject(create_rectangle(
		glm::vec3(-1.0, 1.0, 0.0),
		glm::vec3(1.0, 1.0, 0.0),
		glm::vec3(1.0, 0.0, 0.0),
		glm::vec3(-1.0, 0.0, 0.0),
		glm::vec4(0.0, 0.9, 1.0, 1.0)
	));

	// earth
	scene.addObject(create_rectangle(
		glm::vec3(-1.0, 0.0, 0.0),
		glm::vec3(1.0, 0.0, 0.0),
		glm::vec3(1.0, -1.0, 0.0),
		glm::vec3(-1.0, -1.0, 0.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0)
	));

	// sun
	float sun_depth_back = 0.5;
	scene.addObject(create_circle(
		glm::vec3(0.0, 0.6, sun_depth_back),
		0.2,
		50,
		glm::vec4(1.0, 0.9, 0.0, 0.5),
		sun_depth_back
	));
	float sun_depth_front = 1.0;
	scene.addObject(create_circle(
		glm::vec3(0.0, 0.6, sun_depth_front),
		0.15,
		50,
		glm::vec4(1.0, 0.9, 0.0, 1.0),
		sun_depth_front
	));

	// mountains
	scene.addObject(create_moutains(
		-1, 1, 0.2, 0.5, 3.0, glm::vec4(0.5, 0.27, 0.0, 1.0), 100
	));
	shader_program->bind();
	Engine::RendererUtils::startMainLoop();
}
