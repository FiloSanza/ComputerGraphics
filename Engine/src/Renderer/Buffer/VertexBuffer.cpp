#include "VertexBuffer.h"
#include "../../lib.h"

namespace Engine {
	VertexBuffer::VertexBuffer(std::vector<float> vertices, uint32_t mode)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(
			GL_ARRAY_BUFFER,
			vertices.size() * sizeof(float),
			vertices.data(),
			GL_STATIC_DRAW
		);
	}

	VertexBuffer::VertexBuffer(std::vector<glm::vec3> vertices, uint32_t mode)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(
			GL_ARRAY_BUFFER,
			vertices.size() * sizeof(float) * 3,
			glm::value_ptr(vertices.front()),
			GL_STATIC_DRAW
		);
	}

	VertexBuffer::VertexBuffer(std::vector<Vertex> vertices, uint32_t mode)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(
			GL_ARRAY_BUFFER,
			vertices.size() * sizeof(Vertex) * 3,
			glm::value_ptr(vertices.front().position),
			GL_STATIC_DRAW
		);
	}
	
	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const BufferLayout& VertexBuffer::getLayout() const
	{
		return layout;
	}

	void VertexBuffer::setLayout(const BufferLayout& layout)
	{
		this->layout = layout;
	}

	VertexBuffer VertexBuffer::createStatic(std::vector<float> vertices)
	{
		return VertexBuffer(vertices, GL_STATIC_DRAW);
	}

	VertexBuffer VertexBuffer::createStatic(std::vector<glm::vec3> vertices)
	{
		return VertexBuffer(vertices, GL_STATIC_DRAW);
	}

	VertexBuffer VertexBuffer::createStatic(std::vector<Vertex> vertices)
	{
		return VertexBuffer(vertices, GL_STATIC_DRAW);
	}
}