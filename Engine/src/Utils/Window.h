#pragma once

#include <string>
#include <iostream>

namespace Engine {
	using EnabledWindowEvents = uint32_t;

	enum WindowEvent : uint32_t {
		None			= 0,
		KeyPress		= 1,
		MouseClick		= 1 << 2,
		MouseMovement	= 1 << 3,
		WindowResize	= 1 << 4,
		AllEnabled		= 0xff
	};

	struct WindowOptions {
	public:
		std::string title;
		int width;
		int height;
		int world_width;
		int world_height;
		float aspect_ratio = 2; // Width = 2 * Height

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
		WindowOptions getOptions();

		glm::vec3 convertWindowToWorldCoordinates(glm::vec3 window_coords) {
			// works only if the aspect ratio is the same for world and window coords 
			float delta = ((float)options.world_width) / options.width;
			return window_coords * delta;
		}

		glm::vec3 convertWorldToWindowCoordinates(glm::vec3 world_coords) {
			// works only if the aspect ratio is the same for world and window coords
			float delta = ((float)options.width) / options.world_width;
			return world_coords * delta;
		}

	private:
		void init();

		int id;
		WindowOptions options;
		Keyboard::KeyboardState keyboard_state;
	};

};