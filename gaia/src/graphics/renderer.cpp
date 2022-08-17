#include "pch.h"
#include "renderer.h"

#include <utils/obj_loader.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>

Renderer::Renderer(Config& config)
{
}

bool Renderer::initialize()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Log_Critical("Failed to initialize Glad");
		return false;
	}

	if (!GLAD_GL_VERSION_4_6)
	{
		Log_Error("OpenGL 4.6 unsupported");
		return false;
	}

	// Setup debug callback
	glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)->void
		{
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				Log_Trace("[OpenGL Debug NOTIFICATION] {0}", message);
				break;
			case GL_DEBUG_SEVERITY_LOW:
				Log_Info("[OpenGL Debug LOW] {0}", message);
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				Log_Warn("[OpenGL Debug MEDIUM] {0}", message);
				break;
			case GL_DEBUG_SEVERITY_HIGH:
				Log_Error("[OpenGL Debug HIGH] {0}", message);
				break;
			default:
				break;
			}
		}, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Log_Info("Vendor: {0}", (const char*)glGetString(GL_VENDOR));
	Log_Info("Renderer: {0}", (const char*)glGetString(GL_RENDERER));
	Log_Info("Version: {0}", (const char*)glGetString(GL_VERSION));

	// Load simple mesh
	m_simple_model = new Model("content//meshes//suzanne.obj");

	// Load debug shader
	m_debug_shader = new Shader("debug",{
		"content//shaders//debug.vert",
		"content//shaders//debug.frag"
		});

	return true;
}

void Renderer::render()
{
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_debug_shader->bind();
	m_debug_shader->set_uniform("MVP", mat4{ 1.0f });
	m_simple_model->draw();
}

void Renderer::shutdown()
{
	delete m_simple_model;
	delete m_debug_shader;
}

