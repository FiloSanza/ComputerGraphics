#pragma once

#include <string>

namespace Engine {
	using EnabledWindowEvents = uint32_t;

	enum WindowEvent : uint32_t {
		None			= 0,
		KeyPress		= 1,
		MouseClick		= 1 << 2,
		MouseMovement	= 1 << 3
	};

	struct WindowOptions {
	public:
		std::string title;
		int height;
		int width;

		void enableEvent(WindowEvent event) {
			events |= (uint32_t)event;
		}

		bool isEventEnabled(WindowEvent event) {
			return events & ((uint32_t)event);
		}

	private:
		EnabledWindowEvents events = WindowEvent::None;
	};

	class Window {
	public:
		Window(WindowOptions options);
		~Window();

		bool isKeyPressed(Keyboard::Key key);

	private:
		void init();

		int id;
		WindowOptions options;
		Keyboard::KeyboardState keyboard_state;
	};

};