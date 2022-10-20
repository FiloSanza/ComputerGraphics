#pragma once

#include <string>

namespace Engine {

	class Window {
	public:
		Window(const char* title, int height, int width);
		~Window();

	private:
		void init();

		std::string title;
		int id;
		int height;
		int width;
	};

};