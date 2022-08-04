#include "window.h"

#include <glfw/glfw3.h>

Window::Window(App* app)
{
	auto config = app->m_config;
	m_title = config.m_title;
	m_width = config.m_width;
	m_height = config.m_height;

	m_window_handle = nullptr;
}

bool Window::initialize()
{
	if (!glfwInit())
		return false;

	m_window_handle = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
	if (m_window_handle != nullptr)
		return false;

	glfwMakeContextCurrent(m_window_handle);
	return true;
}

void Window::update()
{
	glfwSwapBuffers(m_window_handle);
	glfwPollEvents();
}

void Window::shutdown()
{
	glfwTerminate();
}
