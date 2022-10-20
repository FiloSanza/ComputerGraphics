#pragma once

#include <functional>
#include <vector>
#include <unordered_map>

#include "Event.h"

namespace Engine {
	
	using EventCallback = std::function<void(const Event&)>;

	class EventsDispatcher {
	public:
		void registerCallback(EventType type, EventCallback function);
		void dispatch(Event event);
		
		static EventsDispatcher& getInstance();
	private:
		EventsDispatcher() {}

		std::unordered_map<EventType, std::vector<EventCallback>> callbacks;
	};

}
