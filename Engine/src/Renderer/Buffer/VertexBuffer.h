#pragma once

#include "BufferLayout.h"

namespace Engine {
	class VertexBuffer {
	public:
		VertexBuffer() = delete;
		VertexBuffer(float* vertices, uint32_t size, uint32_t mode);

		~VertexBuffer() = default;

		void bind() const;
		void unbind() const;

		const BufferLayout& getLayout() const;
		void setLayout(const BufferLayout& layout);

		static VertexBuffer createStatic(float* vertices, uint32_t size);
	private:

		uint32_t id;
		BufferLayout layout;
	};
}