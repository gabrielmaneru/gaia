#include "pch.h"
#include "app.h"

#include "window.h"

App::App(Config& config)
	: m_running(true)
{
	m_window = std::make_shared<Window>(config);
	this->register_event(*this, &App::on_app_termination_request);
}

bool App::start()
{
	if(!m_window->initialize())
		return false;
	return true;
}

void App::run()
{
	do
	{
		m_window->update();
	} while (m_running);
}

void App::end()
{
	m_window->shutdown();
}

void App::on_app_termination_request(const AppTerminationRequestEvent&)
{
	this->m_running = false;
}
