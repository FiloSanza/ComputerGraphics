#pragma once

#include <functional>
#include <vector>
#include <unordered_map>

#include "Event.h"

namespace Engine {
	
	using EventCallback = std::function<bool(Event)>;

	class EventsDispatcher {
	public:
		void registerCallback(EventType type, EventCallback function);
		void dipatch(Event event);
		
		static EventsDispatcher& getInstance();
	private:
		EventsDispatcher() {}

		std::unordered_map<EventType, std::vector<EventCallback>> callbacks;
	};

}
