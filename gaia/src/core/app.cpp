#include "pch.h"
#include "app.h"

#include <window/window.h>
#include <graphics/renderer.h>

App::App(Config& config)
	: m_running(true)
{
	Logger::create();

	this->register_event(*this, &App::on_app_termination_request);

	m_window = std::make_shared<Window>(config);
	m_renderer = std::make_shared<Renderer>(config);
}

bool App::start()
{
	Log_Trace("App::Start");

	if(!m_window->initialize())
		return false;

	if (!m_renderer->initialize())
		return false;

	return true;
}

void App::run()
{
	Log_Trace("App::Run");
	do
	{
		m_renderer->render();
		m_window->update();
	} while (m_running);
}

void App::end()
{
	Log_Trace("App::End");
	m_renderer->shutdown();
	m_window->shutdown();
}

void App::on_app_termination_request(const AppTerminationRequestEvent&)
{
	this->m_running = false;
}
