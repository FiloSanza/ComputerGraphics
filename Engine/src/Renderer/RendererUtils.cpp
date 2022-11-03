#include "RendererUtils.h"
#include "Shader/ShaderProgram.h"

namespace Engine {
	bool RendererUtils::DEBUG_MODE_ENABLED = false;

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
				glDrawElements(gl_draw_mode, spec.vertices, GL_UNSIGNED_INT, (const void*)offset);
				offset += spec.vertices;
			}
			else {
				glDrawArrays(gl_draw_mode, offset, offset + spec.vertices);
				offset += spec.vertices;
			}
		}
	}

	void RendererUtils::updateWindow()
	{
		glutPostRedisplay();
	}

	void RendererUtils::addTimerCallback(Callback callback, uint32_t timeout, int value)
	{
		glutTimerFunc(timeout, callback, value);
	}

	void RendererUtils::uploadUniformMat4(std::string name, glm::mat4 mat)
	{
		ShaderProgram::getActiveInstance()->uploadUniformMat4(name, mat);
	}

	void RendererUtils::uploadUniformFloat(std::string name, float value)
	{
		ShaderProgram::getActiveInstance()->uploadUniformFloat(name, value);
	}

	void RendererUtils::uploadUniformVec2(std::string name, glm::vec2 value)
	{
		ShaderProgram::getActiveInstance()->uploadUniformVec2(name, value);
	}

	float RendererUtils::getElapsedTime()
	{
		return glutGet(GLUT_ELAPSED_TIME);
	}

	void RendererUtils::enableDebugMode()
	{
		setPolygonModeDebug();
		DEBUG_MODE_ENABLED = true;
	}

	void RendererUtils::disableDebugMode()
	{
		disablePolygonModeDebug();
		DEBUG_MODE_ENABLED = false;
	}

	bool RendererUtils::isDebugModeEnabled()
	{
		return DEBUG_MODE_ENABLED;
	}

	void RendererUtils::setPolygonModeDebug()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void RendererUtils::disablePolygonModeDebug() 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	void RendererUtils::enableBlend()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}