#include "VertexBuffer.h"
#include "../../lib.h"

namespace Engine {
	VertexBuffer::VertexBuffer(float* vertices, uint32_t size, uint32_t mode)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
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

	VertexBuffer VertexBuffer::createStatic(float* vertices, uint32_t size)
	{
		return VertexBuffer(vertices, size, GL_STATIC_DRAW);
	}
}