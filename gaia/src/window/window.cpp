#include "pch.h"
#include "window.h"

#include <core/app.h>
#include <events/event_dispatcher.h>

#include <glfw/glfw3.h>

Window::Window(Config& config)
{
	m_title = config.m_title;
	m_width = config.m_width;
	m_height = config.m_height;

	m_handle = nullptr;
	this->register_event(*this, &Window::on_window_resize);
}

bool Window::initialize()
{
	if (!glfwInit())
	{
		Log_Critical("Failed to initialize GLFW");
		return false;
	}

	// Create window
	m_handle = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
	if (m_handle == nullptr)
	{
		Log_Critical("Failed to create window");
		return false;
	}

	// Create context
	glfwMakeContextCurrent(m_handle);

	// Activate vsync
	glfwSwapInterval(1);

	// Store window as userpointer
	glfwSetWindowUserPointer(m_handle, this);

	setup_callbacks();
	return true;
}

void Window::update()
{
	glfwSwapBuffers(m_handle);
	glfwPollEvents();
}

void Window::shutdown()
{
	glfwTerminate();
}

void Window::setup_callbacks()
{
	// Window Resize
	glfwSetWindowSizeCallback(m_handle, [](GLFWwindow*, int w, int h)->void
		{
			WindowResizeEvent event;
			event.m_canvas = { (u32)w, (u32)h };
			EventDispatcher::trigger_event(event);
		});

	// Window Close
	glfwSetWindowCloseCallback(m_handle, [](GLFWwindow*)->void
		{
			EventDispatcher::trigger_event(AppTerminationRequestEvent{});
		});

	// Key Press/Release
	glfwSetKeyCallback(m_handle, [](GLFWwindow* n, int key, int, int action, int)->void
		{
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event;
					event.m_key = key;
					EventDispatcher::trigger_event(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event;
					event.m_key = key;
					EventDispatcher::trigger_event(event);
					break;
				}
			}
		});

	// Key Typed
	glfwSetCharCallback(m_handle, [](GLFWwindow*, u32 codepoint)->void
		{
			KeyTypedEvent event;
			event.m_codepoint = codepoint;
			EventDispatcher::trigger_event(event);
		});

	// Mouse Press/Release
	glfwSetMouseButtonCallback(m_handle, [](GLFWwindow*, int button, int action, int)->void
		{
			switch (action)
			{
				case GLFW_PRESS:
				{
					MousePressedEvent event;
					event.m_button = button;
					EventDispatcher::trigger_event(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseReleasedEvent event;
					event.m_button = button;
					EventDispatcher::trigger_event(event);
					break;
				}
			}
		});

	// Mouse Scroll
	glfwSetScrollCallback(m_handle, [](GLFWwindow*, double xOff, double yOff)->void
		{
			MouseScrolledEvent event;
			event.m_xOff = xOff;
			event.m_yOff = yOff;
			EventDispatcher::trigger_event(event);
		});

	// Cursor Position
	glfwSetCursorPosCallback(m_handle, [](GLFWwindow*, double x, double y)->void
		{
			static double prevx = 0.0, prevy = 0.0;

			MouseMovedEvent event;
			event.m_x = x;
			event.m_y = y;
			event.m_xOff = x - prevx;
			event.m_yOff = y - prevy;
			EventDispatcher::trigger_event(event);

			prevx = x, prevy = y;
		});
}

void Window::on_window_resize(const WindowResizeEvent& event)
{
}
