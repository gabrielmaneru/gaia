#include "pch.h"
#include "shader.h"

#include <utils/file_utils.h>

#include <glad/glad.h>

enum class ShaderType : u32
{
	frag = GL_FRAGMENT_SHADER,
	vert = GL_VERTEX_SHADER,
	geom = GL_GEOMETRY_SHADER,
	tese = GL_TESS_EVALUATION_SHADER,
	tesc = GL_TESS_CONTROL_SHADER
};

Shader::Shader(const char* name, const std::vector<const char*>& paths)
	: m_id(0u)
	, m_name(name)
	, m_paths(paths)
{
	reload();
}

Shader::~Shader()
{
	if (m_id)
		glDeleteProgram(m_id);
}

void Shader::reload()
{
	std::unordered_map<ShaderType, std::string> sources;

	for each (const char* path in m_paths)
	{
		// Get Type from extension
		ShaderType type = get_type(get_extension_from_path(path));

		// Read file content
		std::string file_content = read_file_into_string(path);

		sources[type] = file_content;
	}

	compile(sources);
}

void Shader::bind() const
{
	if (m_id)
		glUseProgram(m_id);
}

void Shader::set_uniform(const char* name, bool val) const
{
	set_uniform(name, val ? 1 : 0);
}

void Shader::set_uniform(const char* name, int val) const
{
	int loc = glGetUniformLocation(m_id, name);
	if (loc >= 0)
		glUniform1i(loc, val);
}

void Shader::set_uniform(const char* name, float val) const
{
	int loc = glGetUniformLocation(m_id, name);
	if (loc >= 0)
		glUniform1f(loc, val);
}

void Shader::set_uniform(const char* name, const vec2& v) const
{
	int loc = glGetUniformLocation(m_id, name);
	if (loc >= 0)
		glUniform2f(loc, v.x, v.y);
}

void Shader::set_uniform(const char* name, const vec3& v) const
{
	int loc = glGetUniformLocation(m_id, name);
	if (loc >= 0)
		glUniform3f(loc, v.x, v.y, v.z);
}

void Shader::set_uniform(const char* name, const vec4& v) const
{
	int loc = glGetUniformLocation(m_id, name);
	if (loc >= 0)
		glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void Shader::set_uniform(const char* name, const mat3& m) const
{
	int loc = glGetUniformLocation(m_id, name);
	if (loc >= 0)
		glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
}

void Shader::set_uniform(const char* name, const mat4& m) const
{
	int loc = glGetUniformLocation(m_id, name);
	if (loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
}

void Shader::compile(const std::unordered_map<ShaderType, std::string>& sources)
{
	if (m_id != 0u)
		glDeleteProgram(m_id);

	u32 program_id = glCreateProgram();
	std::vector<u32> shader_ids;
	for (auto& shaderPair : sources)
	{
		u32 shaderType = (u32)shaderPair.first;
		std::string shaderSource = shaderPair.second;

		u32 shader_id = glCreateShader(shaderType);
		const char* source = shaderSource.data();
		glShaderSource(shader_id, 1, &source, 0);
		glCompileShader(shader_id);

		int compile_result{ 0 };
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_result);
		if (compile_result == GL_FALSE)
		{
			int info_log_length{ 0 };
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

			std::string info_log(info_log_length, 0);
			glGetShaderInfoLog(shader_id, info_log_length, &info_log_length, info_log.data());

			glDeleteShader(shader_id);
			Log_Error("Shader compilation failed due to:\n{0}", info_log.data());
		}

		Log_Assert(compile_result, "Shader compilation failed");
		glAttachShader(program_id, shader_id);
		shader_ids.push_back(shader_id);
	}

	glLinkProgram(program_id);

	int link_result{ 0 };
	glGetProgramiv(program_id, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		int info_log_length{ 0 };
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

		std::string info_log(info_log_length, 0);
		glGetProgramInfoLog(program_id, info_log_length, &info_log_length, info_log.data());

		glDeleteProgram(program_id);

		for each (u32 shader_id in shader_ids)
			glDeleteShader(shader_id);

		Log_Error("Shader program linking failed due to:\n{0}", info_log.data());
	}

	Log_Assert(link_result, "Shader progam linking failed");

	for each (u32 shader_id in shader_ids)
		glDetachShader(program_id, shader_id);

	m_id = program_id;
}

ShaderType Shader::get_type(std::string extension)
{
	if (strcmp(extension.data(), "frag") == 0)
		return ShaderType::frag;
	if (strcmp(extension.data(), "vert") == 0)
		return ShaderType::vert;
	if (strcmp(extension.data(), "geom") == 0)
		return ShaderType::geom;
	if (strcmp(extension.data(), "tese") == 0)
		return ShaderType::tese;
	if (strcmp(extension.data(), "tesc") == 0)
		return ShaderType::tesc;

	Log_Assert(false, "Unknown shader type with extension: {0}", extension);
	// Prevent "not all control paths return a value" warning
	return ShaderType::frag;
}
