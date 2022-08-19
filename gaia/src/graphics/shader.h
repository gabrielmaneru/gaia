#pragma once

enum class ShaderType : u32;

class Shader
{
public:
	Shader(const char* name, const std::vector<const char*>& paths);
	~Shader();
	void reload();
	void bind()const;
	void set_uniform(const char* name, bool val) const;
	void set_uniform(const char* name, int val) const;
	void set_uniform(const char* name, float val) const;
	void set_uniform(const char* name, const vec2& v) const;
	void set_uniform(const char* name, const vec3& v) const;
	void set_uniform(const char* name, const vec4& v) const;
	void set_uniform(const char* name, const mat3& m) const;
	void set_uniform(const char* name, const mat4& m) const;

private:
	void compile(const std::unordered_map<ShaderType, std::string>& sources);
	static ShaderType get_type(std::string extension);

	u32 m_id;
	const char* m_name;
	std::vector<const char*> m_paths;
};