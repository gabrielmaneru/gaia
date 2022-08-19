#pragma once

#define Extensions(...) static constexpr Extension m_extensions[]={__VA_ARGS__}

enum class Extension {
	_none,
	_begin,
	png,
	jpg,
	obj,
	level,
	mtl,
	_end
};
inline Extension operator++(Extension& val);

Extension get_extension(const std::string& path);