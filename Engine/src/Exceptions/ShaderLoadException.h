#pragma once

#include <stdexcept>

namespace Engine {
	class ShaderLoadException : std::runtime_error {
	public:
		using std::runtime_error::runtime_error;
		using std::runtime_error::what;
	};
}