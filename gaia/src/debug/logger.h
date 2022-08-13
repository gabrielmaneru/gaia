#pragma once
#include <spdlog/spdlog.h>

namespace Log
{
	void create_logger();
	void Trace(const char* msg);
	void Info(const char* msg);
	void Warn(const char* msg);
	void Error(const char* msg);
	void Critical(const char* msg);
	extern std::shared_ptr<spdlog::logger> s_logger;
};