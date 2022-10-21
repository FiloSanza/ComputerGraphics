#include "RendererUtils.h"

namespace Engine {
	void RendererUtils::init(int& argc, char** argv)
	{
		glutInit(&argc, argv);
		glutInitContextVersion(4, 0);
		glutInitContextProfile(GLUT_CORE_PROFILE);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glewExperimental = GL_TRUE;
	}

	void RendererUtils::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RendererUtils::setDisplayFunc(draw_func_t func)
	{
		glutDisplayFunc(func);
	}

	void RendererUtils::startMainLoop()
	{
		glutMainLoop();
	}

	void RendererUtils::swapBuffers()
	{
		glutSwapBuffers();
	}

	void RendererUtils::clear(int mask) {
		glClear(mask);
	}

	void RendererUtils::draw(const std::shared_ptr<VertexArray> vertex_array, DrawMode draw_mode, uint32_t vertex_count)
	{
		vertex_array->bind();

		uint32_t count = vertex_count ? vertex_count : vertex_array->getVertexCount();
		glDrawArrays(drawModeToGLMode(draw_mode), 0, count);
	}

	void RendererUtils::drawIndexed(const std::shared_ptr<VertexArray> vertex_array, DrawMode draw_mode, uint32_t index_count)
	{
		auto index_buffer = vertex_array->getIndexBuffer();

		vertex_array->bind();
		index_buffer->bind();
		uint32_t count = index_count ? index_count : index_buffer->getCount();
		glDrawElements(drawModeToGLMode(draw_mode), count, GL_UNSIGNED_INT, nullptr);
	}

	void RendererUtils::setPolygonModeDebug()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	
	void RendererUtils::enableBlend()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}