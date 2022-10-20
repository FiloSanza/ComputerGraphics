#pragma once

#include "../Utils/Input.h"

namespace Engine {
	
	enum class EventType {
		KeyPressed = 0,
		KeyReleased,
		MouseClick,
		MouseMoved
	};

	class Event {
	public:
		EventType getType() const { return type; }
		Keyboard::Key getKey() const { return key; }
		int getMouseX() const { return mouse_x; }
		int getMouseY() const { return mouse_y; }
		Mouse::Button getMouseButton() const { return mouse_button; }
		Mouse::ButtonState getMouseButtonState() const { return mouse_button_state; }

		void setType(EventType type) { this->type = type; }
		void setKey(Keyboard::Key key) { this->key = key; }
		void setMouseX(int x) { mouse_x = x; }
		void setMouseY(int y) { mouse_y = y; }
		void setMouseButton(Mouse::Button button) { mouse_button = button; }
		void setMouseButtonState(Mouse::ButtonState state) { mouse_button_state = state; }

		static Event createKeyPressedEvent(Keyboard::Key key, int x = -1, int y = -1) {
			auto evt = Event();
			evt.setType(EventType::KeyPressed);
			evt.setKey(key);
			evt.setMouseX(x);
			evt.setMouseY(y);
			return evt;
		}

		static Event createKeyReleasedEvent(Keyboard::Key key, int x = -1, int y = -1) {
			auto evt = Event();
			evt.setType(EventType::KeyReleased);
			evt.setKey(key);
			evt.setMouseX(x);
			evt.setMouseY(y);
			return evt;
		}

		static Event createMouseClickEvent(Mouse::Button button, int x = -1, int y = -1) {
			auto evt = Event();
			evt.setType(EventType::MouseClick);
			evt.setMouseButton(button);
			evt.setMouseButtonState(Mouse::ButtonState::Down);
			evt.setMouseX(x);
			evt.setMouseY(y);
			return evt;
		}

		static Event createMouseMovedEvent(int x, int y) {
			auto evt = Event();
			evt.setType(EventType::MouseMoved);
			evt.setMouseX(x);
			evt.setMouseY(y);
			return evt;
		}
	private:
		Event() {}

		EventType type;
		Keyboard::Key key;
		int mouse_x;
		int mouse_y;
		Mouse::Button mouse_button;
		Mouse::ButtonState mouse_button_state;
	};

}