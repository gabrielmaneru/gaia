#pragma once
#include "config.h"
#include <events/event_listener.h>

struct AppTerminationRequestEvent : public iEvent { };

// Modules
class Window;
class Renderer;

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

	// Modules
	std::shared_ptr<Window> m_window;
	std::shared_ptr<Renderer> m_renderer;
};
