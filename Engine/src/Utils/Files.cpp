#include "Files.h"

#include <fstream>
#include <sstream>

namespace Engine {
	std::string Engine::File::readAllAsString(std::string path)
	{
		std::ifstream in(path);
		std::stringstream buffer;
		buffer << in.rdbuf();
		return buffer.str();
	}
}