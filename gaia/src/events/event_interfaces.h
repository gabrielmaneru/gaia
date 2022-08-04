#pragma once

struct iEvent
{
	virtual ~iEvent() = default;
};

class iHandler
{
public:
	virtual ~iHandler() = default;
	virtual void call(const iEvent&) = 0;
	virtual void handle(const iEvent& e) final { call(e); };
};

class iListener
{
public:
	virtual ~iListener() = default;
private:
	friend class EventDispatcher;
	virtual void handle_event(const iEvent&) = 0;
};