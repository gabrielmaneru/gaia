#include "pch.h"
#include "event_dispatcher.h"

EventDispatcher EventDispatcher::instance = {};

void EventDispatcher::trigger_event(const iEvent& event)
{
	// Tries to find the event in the Map
	auto it = instance.m_listeners.find(type_of(event));

	if (it == instance.m_listeners.cend())
		return;

	// Handle the event for each Listener
	for (u32 i = 0; i < it->second.size(); i++)
		it->second[i]->handle_event(event);
}

void EventDispatcher::subscribe(iListener& listener, TypeInfo type)
{
	instance.m_listeners[type].push_back(&listener);
}

void EventDispatcher::unsubscribe(iListener& listener, TypeInfo type)
{
	// Tries to find the event in the Map
	auto it = instance.m_listeners.find(type);
	if (it == instance.m_listeners.end())
		return;

	// Search the Listener and erase it
	for (u32 i = 0; i < it->second.size(); i++)
		if (it->second[i] == &listener)
			it->second.erase(it->second.begin() + i);
}
