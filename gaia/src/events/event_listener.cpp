#include "pch.h"
#include "event_listener.h"
#include "event_dispatcher.h"

EventListener::~EventListener()
{
	for (auto& it : collection)
	{
		EventDispatcher::unsubscribe(*this, it.first);
		delete it.second;
	}
}

void EventListener::handle_event(const iEvent& event)
{
	//Tries to find the event in the Map
	auto search = collection.find(type_of(event));

	if (search != collection.end())
		search->second->handle(event);
}
