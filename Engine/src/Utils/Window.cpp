#pragma once

#include <cassert>

#include "../Events/EventsDispatcher.h"
#include "../Events/Event.h"
#include "../lib.h"
#include "Window.h"
#include "Key.h"

namespace Engine {
	Window::Window(const char* title, int height, int width)
		: title(title), height(height), width(width)
	{
		init();
	}

	Window::~Window() {
		glutDestroyWindow(id);
	}

	void Window::init()
	{
		glutInitWindowSize(width, height);
		glutInitWindowPosition(100, 100);
		id = glutCreateWindow(title.c_str());

		int fail = glewInit();
		
		//TODO: handle
		assert(!fail);

		glutKeyboardFunc([](KeyCode key, int x, int y) {
			auto evt = Event::createKeyPressedEvent((Keys)key);
			EventsDispatcher::getInstance().dipatch(evt);
		});
	}
}