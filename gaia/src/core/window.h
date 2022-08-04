#pragma once
#include "app.h"

struct GLFWwindow;
class Window
{
	GLFWwindow* m_window_handle;
	const char* m_title;
	int m_width;
	int m_height;

public:
	Window(App* app);
	bool initialize();
	void update();
	void shutdown();
};