#pragma once

#include <cassert>
#include <iostream>

#include "../Events/EventsDispatcher.h"
#include "../Events/Event.h"
#include "../lib.h"
#include "Window.h"
#include "Input.h"

namespace Engine {
	Window::Window(WindowOptions options)
		: options(options)
	{
		init();
	}

	Window::~Window() {
		glutDestroyWindow(id);
	}

	void Window::init()
	{
		glutInitWindowSize(options.width, options.height);
		glutInitWindowPosition(100, 100);
		id = glutCreateWindow(options.title.c_str());

		int fail = glewInit();
		
		//TODO: handle
		assert(!fail);

		if (options.isEventEnabled(WindowEvent::KeyPress)) {
			glutKeyboardFunc([](Keyboard::KeyCode key, int x, int y) {
				auto evt = Event::createKeyPressedEvent((Keyboard::Key)key);
				EventsDispatcher::getInstance().dispatch(evt);
			});
		}

		if (options.isEventEnabled(WindowEvent::MouseClick)) {
			glutMouseFunc([](Mouse::ButtonType button, Mouse::StateType state, int x, int y) {
				if (state != GLUT_DOWN) {
					return;
				}

				// We might get different events if the mouse wheel is srolled
				// we do not handle them here.
				// This happens if glutMouseWheelFunc is not used.
				if (button < 0 || button > 2) {
					return;
				}

				auto evt = Event::createMouseClickEvent((Mouse::Button)button);
				EventsDispatcher::getInstance().dispatch(evt);
			});
		}

		if (options.isEventEnabled(WindowEvent::MouseMovement)) {
			auto mouse_movement_callback = [](int x, int y) {
				auto evt = Event::createMouseMovedEvent(x, y);
				EventsDispatcher::getInstance().dispatch(evt);
			};

			// Used for mouse movements while the mouse is clicked
			glutMotionFunc(mouse_movement_callback);
			// Used for mouse movements while the mouse is NOT clicked
			glutPassiveMotionFunc(mouse_movement_callback);
		}
	}
}