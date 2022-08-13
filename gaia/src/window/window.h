#pragma once
#include <core/config.h>

struct GLFWwindow;
class Window
{
public:
	Window(Config& config);
	bool initialize();
	void update();
	void shutdown();

private:
	GLFWwindow* m_window_handle;
	const char* m_title;
	int m_width;
	int m_height;
};
