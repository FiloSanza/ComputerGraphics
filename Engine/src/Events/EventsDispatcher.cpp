#include "EventsDispatcher.h"

#include <algorithm>

namespace Engine {

	void EventsDispatcher::registerCallback(EventType type, EventCallback function)
	{
		callbacks[type].push_back(function);
	}
	
	void EventsDispatcher::dipatch(Event event)
	{
		std::for_each(callbacks[event.getType()].begin(), callbacks[event.getType()].end(), 
			[event](const EventCallback& callback) {
				callback(event);
			}
		);
	}
	
	EventsDispatcher& EventsDispatcher::getInstance()
	{
		static EventsDispatcher dispatcher;

		return dispatcher;
	}

}