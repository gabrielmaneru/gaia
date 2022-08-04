#pragma once
#include "event_interfaces.h"
#include "type_info.h"


class EventDispatcher {
public:
	static void trigger_event(const iEvent&);

private:
	friend class EventListener;
	static void subscribe(iListener&, TypeInfo);
	static void unsubscribe(iListener&, TypeInfo);
	static EventDispatcher instance;
	EventDispatcher() = default;
	std::map<TypeInfo, std::vector<iListener*> > m_listeners;
};