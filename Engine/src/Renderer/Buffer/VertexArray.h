#pragma once

#include <vector>
#include <memory>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "../../lib.h"

namespace Engine {
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void bind();
		void unbind();
		
		std::vector<std::shared_ptr<VertexBuffer>>& getBuffers();
		std::shared_ptr<IndexBuffer> getIndexBuffer();
		uint32_t getVertexCount();

		void addVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
		void setVertexCount(uint32_t count);
		void setIndexBuffer(std::shared_ptr<IndexBuffer> new_index_buffer);
	private:
		uint32_t id;
		uint32_t vertex_count;
		uint32_t vertex_attrib_count;
		std::vector<std::shared_ptr<VertexBuffer>> buffers;
		std::shared_ptr<IndexBuffer> index_buffer;
	};
}