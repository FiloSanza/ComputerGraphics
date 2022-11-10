#pragma once

#include <vector>

#include "BufferLayout.h"
#include "DataTypes.h"
#include "../../lib.h"

namespace Engine {
	class VertexBuffer {
	public:
		~VertexBuffer() = default;

		void bind() const;
		void unbind() const;

		void setVertices(std::vector<float> vertices);
		void setVertices(std::vector<glm::vec3> vertices);
		void setVertices(std::vector<Vertex> vertices);
		void setVertices(std::vector<TextureVertex> vertices);
		const BufferLayout& getLayout() const;
		void setLayout(const BufferLayout& layout);

		static VertexBuffer createStatic(std::vector<float> vertices);
		static VertexBuffer createStatic(std::vector<glm::vec3> vertices);
		static VertexBuffer createStatic(std::vector<Vertex> vertices);
		static VertexBuffer createStatic(std::vector<TextureVertex> vertices);
		static VertexBuffer createDynamic(uint32_t size);
	private:
		VertexBuffer(std::vector<float> vertices, bool is_dynamic);
		VertexBuffer(std::vector<glm::vec3> vertices, bool is_dynamic);
		VertexBuffer(std::vector<Vertex> vertices, bool is_dynamic);
		VertexBuffer(std::vector<TextureVertex> vertices, bool is_dynamic);
		VertexBuffer(uint32_t size);

		bool is_dynamic;
		uint32_t id;
		BufferLayout layout;
	};
}