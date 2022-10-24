#include "IndexBuffer.h"
#include "../../lib.h"

namespace Engine {
	IndexBuffer::IndexBuffer(const uint32_t* indices, const uint32_t count)
		: count(count)
	{
		glGenBuffers(1, &id);

		// GL_ELEMENT_ARRAY_BUFFER is only valid if a VAO is binded, load the data as GL_ARRAY_BUFFER
		// and bind it later as GL_ELEMENT_ARRAY_BUFFER 
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_STATIC_DRAW);
	}

	IndexBuffer::IndexBuffer(const std::vector<uint32_t>& indices)
	{
		count = indices.size();
		glGenBuffers(1, &id);

		// GL_ELEMENT_ARRAY_BUFFER is only valid if a VAO is binded, load the data as GL_ARRAY_BUFFER
		// and bind it later as GL_ELEMENT_ARRAY_BUFFER 
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * count, indices.data(), GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void IndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void IndexBuffer::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);
	}

	uint32_t IndexBuffer::getCount()
	{
		return count;
	}
}