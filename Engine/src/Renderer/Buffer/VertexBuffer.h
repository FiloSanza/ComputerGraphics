#pragma once

#include <vector>

#include "BufferLayout.h"
#include "../../lib.h"

namespace Engine {
	class VertexBuffer {
	public:
		VertexBuffer() = delete;
		VertexBuffer(std::vector<float> vertices, uint32_t mode);
		VertexBuffer(std::vector<glm::vec3> vertices, uint32_t mode);

		~VertexBuffer() = default;

		void bind() const;
		void unbind() const;

		const BufferLayout& getLayout() const;
		void setLayout(const BufferLayout& layout);

		static VertexBuffer createStatic(std::vector<float> vertices);
		static VertexBuffer createStatic(std::vector<glm::vec3> vertices);
	private:

		uint32_t id;
		BufferLayout layout;
	};
}