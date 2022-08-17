#version 460 core
layout (location = 0) in vec3  a_position;
layout (location = 1) in vec3  a_normal;
layout (location = 2) in vec2  a_uv;

uniform mat4 MVP;

out vec4 v_color;

void main()
{
	v_color = vec4(a_position, 1.0);
	gl_Position = MVP*vec4(a_position, 1.0);
}