#pragma once

class Window;
struct App
{
	struct Config
	{
		const char* m_title;
		int m_width;
		int m_height;
	};

	App(Config& config);
	bool start();
	void run();
	void end();

	bool m_running;
	Config m_config;
	Window* m_window;
};