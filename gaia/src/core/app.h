#pragma once
#include "config.h"
#include <events/event_listener.h>
#include <memory>

struct AppTerminationRequestEvent : public iEvent { };

class Window;
class App : public EventListener
{
public:
	App(Config& config);
	bool start();
	void run();
	void end();

private:
	void on_app_termination_request(const AppTerminationRequestEvent&);

	bool m_running;
	std::shared_ptr<Window> m_window;
};
