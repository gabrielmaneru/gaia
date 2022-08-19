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
	~App();
	bool start();
	void run();
	void end();

private:
	void on_app_termination_request(const AppTerminationRequestEvent&);
	bool m_running;

	// Modules
	shared<Window> m_window;
	shared<Renderer> m_renderer;
};
