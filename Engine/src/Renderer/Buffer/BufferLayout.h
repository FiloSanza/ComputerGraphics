#pragma once

#include <vector>
#include "BufferElement.h"

namespace Engine {
	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(std::initializer_list<BufferElement> elements) : elements(elements), stride(0) {
			for (auto& element : this->elements) {
				element.offset = stride;
				stride += element.size;
			};
		};

		uint32_t getStride() { return stride; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.end(); }
	private:
		std::vector<BufferElement> elements;
		uint32_t stride = 0;
	};
}