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

	bool Window::isKeyPressed(Keyboard::Key key)
	{
		return keyboard_state.isPressed(key);
	}

	WindowOptions Window::getOptions()
	{
		return options;
	}

	void Window::init()
	{
		srand(time(nullptr));
		glutInitWindowSize(options.width, options.height);
		glutInitWindowPosition(100, 100);
		id = glutCreateWindow(options.title.c_str());

		int fail = glewInit();
		
		assert(!fail);

		if (options.isEventEnabled(WindowEvent::KeyPress)) {
			glutKeyboardFunc([](Keyboard::KeyCode key, int x, int y) {
				auto evt = Event::createKeyPressedEvent((Keyboard::Key)key);
				EventsDispatcher::getInstance().dispatch(evt);
			});

			glutKeyboardUpFunc([](Keyboard::KeyCode key, int x, int y) {
				auto evt = Event::createKeyReleasedEvent((Keyboard::Key)key);
				EventsDispatcher::getInstance().dispatch(evt);
			});

			glutIgnoreKeyRepeat(1);

			EventsDispatcher::getInstance().registerCallback(EventType::KeyPressed, [this](const Event& evt) {
				keyboard_state.setPressed(evt.getKey(), true);
			});

			EventsDispatcher::getInstance().registerCallback(EventType::KeyReleased, [this](const Event& evt) {
				keyboard_state.setPressed(evt.getKey(), false);
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

				auto evt = Event::createMouseClickEvent((Mouse::Button)button, x, y);
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

		if (options.isEventEnabled(WindowEvent::WindowResize)) {
			glutReshapeFunc([](int width, int height) {
				auto evt = Event::createWindowResizeEvent(width, height);
				EventsDispatcher::getInstance().dispatch(evt);
			});

			EventsDispatcher::getInstance().registerCallback(EventType::WindowResize, [this](const Event& evt) {
				// We want to keep the right aspect ratio
				float new_height = (float)evt.getHeight();
				float new_width = (float)evt.getWidth();
				float new_ratio = new_width / new_height;

				if (new_ratio < options.aspect_ratio) {
					new_width = options.aspect_ratio * new_height;
					glutReshapeWindow(new_width, new_height);
					glViewport(0, 0, new_width, new_height);
				}
				else if (new_ratio > options.aspect_ratio) {
					new_height = new_width / options.aspect_ratio;
					glutReshapeWindow(new_width, new_height);
					glViewport(0, 0, new_width, new_height);
				}

				options.width = new_width;
				options.height = new_height;
			});
		}
	}
}