#pragma once

#include <stdint.h>

namespace Engine {
	class IndexBuffer {
	public:
		IndexBuffer(const uint32_t* indices, const uint32_t count);
		~IndexBuffer();

		void bind();
		void unbind();

		uint32_t getCount();
	
	private:
		uint32_t id;
		uint32_t count;
	};
}