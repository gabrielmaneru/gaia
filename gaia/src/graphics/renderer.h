#pragma once
#include "shader.h"
#include "model.h"

#include <core/config.h>

class Renderer
{
public:
	Renderer(Config& config);
	bool initialize();
	void render();
	void shutdown();

private:
	Model* m_simple_model{ nullptr };
	Shader* m_debug_shader{ nullptr };
};