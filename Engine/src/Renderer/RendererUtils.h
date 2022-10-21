#pragma once

#include "../lib.h"
#include "Buffer/VertexArray.h"
#include "Buffer/DataTypes.h"
#include <string>
#include <memory>

namespace Engine {

	enum ClearOptions {
		ColorBuffer = GL_COLOR_BUFFER_BIT,
	};

	class RendererUtils {
	public:
		typedef void (*draw_func_t)(void);

		static void init(int& argc, char** argv);
		static void setClearColor(const glm::vec4& color);
		static void setDisplayFunc(draw_func_t func);
		static void startMainLoop();
		static void swapBuffers();
		static void clear(int mask);
		static void draw(const std::shared_ptr<VertexArray> vertex_array, DrawMode draw_mode, uint32_t vertex_count = 0);
		static void drawIndexed(const std::shared_ptr<VertexArray> vertex_array, DrawMode draw_mode, uint32_t index_count = 0);
		static void setPolygonModeDebug();
		static void enableBlend();
	};

}