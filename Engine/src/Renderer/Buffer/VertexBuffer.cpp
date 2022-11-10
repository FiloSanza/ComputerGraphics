#include "VertexBuffer.h"
#include "../../lib.h"

namespace Engine {
	VertexBuffer::VertexBuffer(std::vector<float> vertices, bool is_dynamic)
		: is_dynamic(is_dynamic)
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

	VertexBuffer::VertexBuffer(std::vector<glm::vec3> vertices, bool is_dynamic)
		: is_dynamic(is_dynamic)
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

	VertexBuffer::VertexBuffer(std::vector<Vertex> vertices, bool is_dynamic)
		: is_dynamic(is_dynamic)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(
			GL_ARRAY_BUFFER,
			vertices.size() * sizeof(Vertex),
			glm::value_ptr(vertices.front().position),
			GL_STATIC_DRAW
		);
	}

	VertexBuffer::VertexBuffer(std::vector<TextureVertex> vertices, bool is_dynamic)
		: is_dynamic(is_dynamic)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(
			GL_ARRAY_BUFFER,
			vertices.size() * sizeof(TextureVertex),
			glm::value_ptr(vertices.front().position),
			GL_STATIC_DRAW
		);
	}

	VertexBuffer::VertexBuffer(uint32_t size) : is_dynamic(true) {
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(
			GL_ARRAY_BUFFER,
			size,
			nullptr,
			GL_DYNAMIC_DRAW
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

	void VertexBuffer::setVertices(std::vector<float> vertices)
	{
		if (!is_dynamic)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0, 
			sizeof(vertices), 
			vertices.data()
		);
	}

	void VertexBuffer::setVertices(std::vector<glm::vec3> vertices)
	{
		if (!is_dynamic)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0,
			sizeof(glm::vec3) * vertices.size(),
			glm::value_ptr(vertices.front())
		);
	}

	void VertexBuffer::setVertices(std::vector<Vertex> vertices)
	{
		if (!is_dynamic)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0,
			sizeof(Vertex) * vertices.size(),
			glm::value_ptr(vertices.front().position)
		);
	}

	void VertexBuffer::setVertices(std::vector<TextureVertex> vertices)
	{
		if (!is_dynamic)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0,
			sizeof(TextureVertex) * vertices.size(),
			glm::value_ptr(vertices.front().position)
		);
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
		return VertexBuffer(vertices, false);
	}

	VertexBuffer VertexBuffer::createStatic(std::vector<glm::vec3> vertices)
	{
		return VertexBuffer(vertices, false);
	}

	VertexBuffer VertexBuffer::createStatic(std::vector<Vertex> vertices)
	{
		return VertexBuffer(vertices, false);
	}

	VertexBuffer VertexBuffer::createStatic(std::vector<TextureVertex> vertices)
	{
		return VertexBuffer(vertices, false);
	}

	VertexBuffer VertexBuffer::createDynamic(uint32_t size)
	{
		return VertexBuffer(size);
	}
}