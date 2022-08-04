#include "app.h"

#ifndef ENTRY_POINT
#define ENTRY_POINT
int main(int, char**)
{
	// Create application
	auto appconfig = App::Config();
	appconfig.m_title = "gaia";
	appconfig.m_width = 1280;
	appconfig.m_height = 720;
	auto app = App(appconfig);

	// Execute application
	if (app.start())
		return -1;
	app.run();
	app.end();
	return 0;
}
#endif // !ENTRY_POINT