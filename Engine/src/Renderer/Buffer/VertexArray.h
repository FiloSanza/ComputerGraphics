#pragma once

#include <vector>
#include <memory>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "../../lib.h"

namespace Engine {
	struct DrawSpec {
		uint32_t vertices;
		DrawMode draw_mode;
	};

	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void bind();
		void unbind();
		
		bool isIndexed();
		std::vector<std::shared_ptr<VertexBuffer>>& getBuffers();
		std::shared_ptr<IndexBuffer> getIndexBuffer();
		const std::vector<DrawSpec>& getDrawSpecs();

		void addVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
		void setIndexBuffer(std::shared_ptr<IndexBuffer> new_index_buffer);
		void setDrawSpecs(std::initializer_list<DrawSpec> specs);
	private:
		uint32_t id;
		bool is_indexed;
		uint32_t vertex_attrib_count;
		std::vector<std::shared_ptr<VertexBuffer>> buffers;
		std::shared_ptr<IndexBuffer> index_buffer;
		std::vector<DrawSpec> draw_specs;
	};
}