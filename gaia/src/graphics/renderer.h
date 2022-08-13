#pragma once
#include <core/config.h>

class Renderer
{
public:
	Renderer(Config& config);
	bool initialize();
	void render();

private:

};