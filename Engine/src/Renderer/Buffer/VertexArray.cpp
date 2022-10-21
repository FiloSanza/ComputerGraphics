#include "VertexArray.h"
#include "DataTypes.h"

namespace Engine {
	VertexArray::VertexArray() 
		: vertex_attrib_count(0), vertex_count(0)
	{
		glGenVertexArrays(1, &id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(id);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::addVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
	{
		glBindVertexArray(id);
		buffer->bind();

		auto layout = buffer->getLayout();
		for (auto element : layout) {
			glEnableVertexAttribArray(vertex_attrib_count);
			glVertexAttribPointer(
				vertex_attrib_count,
				element.getComponentCount(),
				ShaderDataTypeToGLType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.offset
			);
			vertex_attrib_count++;
		}

		buffers.push_back(buffer);
	}

	void VertexArray::setVertexCount(uint32_t count)
	{
		vertex_count = count;
	}

	std::vector<std::shared_ptr<VertexBuffer>>& VertexArray::getBuffers()
	{
		return buffers;
	}

	void VertexArray::setIndexBuffer(std::shared_ptr<IndexBuffer> new_index_buffer)
	{
		index_buffer = new_index_buffer;
	}

	std::shared_ptr<IndexBuffer> VertexArray::getIndexBuffer()
	{
		return index_buffer;
	}
	uint32_t VertexArray::getVertexCount()
	{
		return vertex_count;
	}
}