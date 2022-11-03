#include <memory>
#include "Window.h"
#include "../Renderer/Shader/ShaderProgram.h"

namespace Engine {
	class GraphicContext {
	public:
		GraphicContext(std::shared_ptr<Window> window, std::shared_ptr<ShaderProgram> program)
			: program(program), window(window) {}

		std::shared_ptr<Engine::Window> getWindow() { return window; }
		std::shared_ptr<Engine::ShaderProgram> getShaderProgram() { return program; }
	private:
		std::shared_ptr<Engine::Window> window;
		std::shared_ptr<Engine::ShaderProgram> program;
	};
}