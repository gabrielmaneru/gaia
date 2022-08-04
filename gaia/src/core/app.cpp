#include "app.h"
#include "window.h"

App::App(Config& config)
	: m_config(config)
{
	m_window = new Window(this);
	m_running = false;
}

bool App::start()
{
	if(m_window->initialize())
		return false;
}

void App::run()
{
	m_running = true;
	do
	{
		m_window->update();
	} while (m_running);
}

void App::end()
{
	m_window->shutdown();
}
