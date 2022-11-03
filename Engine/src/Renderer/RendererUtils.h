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
		typedef void (*DrawFunc)(void);
		typedef void (*Callback)(int);

		static void init(int& argc, char** argv);
		static void setClearColor(const glm::vec4& color);
		static void setDisplayFunc(DrawFunc func);
		static void startMainLoop();
		static void swapBuffers();
		static void clear(int mask);
		static void draw(const std::shared_ptr<VertexArray>& vertex_array);
		static void setPolygonModeDebug();
		static void disablePolygonModeDebug();
		static void enableBlend();
		static void updateWindow();
		static void addTimerCallback(Callback callback, uint32_t timeout, int value);
		static void uploadUniformMat4(std::string name, glm::mat4 mat);
		static void uploadUniformFloat(std::string name, float value);
		static void uploadUniformVec2(std::string name, glm::vec2 value);
		static float getElapsedTime();
		static void enableDebugMode();
		static void disableDebugMode();
		static bool isDebugModeEnabled();

	private:
		static bool DEBUG_MODE_ENABLED;
	};

}