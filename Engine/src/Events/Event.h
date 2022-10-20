#pragma once

#include "../Utils/Key.h"

namespace Engine {
	
	enum class EventType {
		KeyPressed = 0,
		KeyReleased,
	};

	class Event {
	public:
		Event(EventType type) : type(type) {}

		EventType getType() const { return type; }
		KeyCode getKey() const { return key; }

		void setKey(Keys key) { this->key = key; }

		static Event createKeyPressedEvent(Keys key) {
			auto evt = Event(EventType::KeyPressed);
			evt.setKey(key);
			return evt;
		}

		static Event createKeyReleasedEvent(Keys key) {
			auto evt = Event(EventType::KeyReleased);
			evt.setKey(key);
			return evt;
		}
	private:
		EventType type;
		Keys key;
	};

}