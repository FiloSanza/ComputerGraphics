#pragma once
#include <string>

namespace Engine {
	class File {
	public:
		static std::string readAllAsString(std::string path);
	};
}