#include "RendererUtils.h"

namespace Engine {
	void RendererUtils::init(int& argc, char** argv, int width, int height, int pos_x, int pos_y, const std::string& title)
	{
		glutInit(&argc, argv);
		glutInitContextVersion(4, 0);
		glutInitContextProfile(GLUT_CORE_PROFILE);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glewExperimental = GL_TRUE;
		glutInitWindowSize(width, height);
		glutInitWindowPosition(pos_x, pos_y);
		glutCreateWindow(title.c_str());
		glewInit();
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

	void RendererUtils::drawLines(const std::shared_ptr<VertexArray> vertex_array, uint32_t vertex_count)
	{
		vertex_array->bind();
		glDrawArrays(GL_LINES, 0, vertex_count);
	}

	void RendererUtils::drawIndexed(const std::shared_ptr<VertexArray> vertex_array, uint32_t index_count)
	{
		auto index_buffer = vertex_array->getIndexBuffer();

		vertex_array->bind();
		index_buffer->bind();
		uint32_t count = index_count ? index_count : index_buffer->getCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void RendererUtils::setPolygonModeDebug()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}