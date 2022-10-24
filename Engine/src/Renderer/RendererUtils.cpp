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

	void RendererUtils::setDisplayFunc(DrawFunc func)
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

	void RendererUtils::draw(const std::shared_ptr<VertexArray>& vertex_array)
	{
		auto draw_specs = vertex_array->getDrawSpecs();

		vertex_array->bind();

		uint32_t offset = 0;
		for (const auto& spec : draw_specs) {
			const auto gl_draw_mode = drawModeToGLMode(spec.draw_mode);
			if (vertex_array->isIndexed()) {
				vertex_array->getIndexBuffer()->bind();
				glDrawElements(gl_draw_mode, spec.vertices, GL_UNSIGNED_INT, (const void*) offset);
				offset += spec.vertices;
			} else {
				glDrawArrays(gl_draw_mode, offset, offset + spec.vertices);
				offset += spec.vertices;
			}
		}
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