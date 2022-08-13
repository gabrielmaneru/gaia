#pragma once
#include <core/config.h>
#include <events/event_listener.h>

struct WindowResizeEvent : public iEvent { urect m_canvas; };

struct KeyPressedEvent : public iEvent { int m_key; };
struct KeyReleasedEvent : public iEvent { int m_key; };
struct KeyTypedEvent : public iEvent { u32 m_codepoint; };

struct MousePressedEvent : public iEvent { int m_button; };
struct MouseReleasedEvent : public iEvent { int m_button; };
struct MouseScrolledEvent : public iEvent { double m_xOff, m_yOff; };
struct MouseMovedEvent : public iEvent { float m_x, m_y, m_xOff, m_yOff; };

struct GLFWwindow;
class Window : public EventListener
{
public:
	Window(Config& config);
	bool initialize();
	void update();
	void shutdown();

private:
	void setup_callbacks();
	void on_window_resize(const WindowResizeEvent& event);

	GLFWwindow* m_handle;
	const char* m_title;
	int m_width;
	int m_height;
};
