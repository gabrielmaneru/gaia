#pragma once
#include <spdlog/spdlog.h>

namespace Logger
{
	void create();
	extern std::shared_ptr<spdlog::logger> s_logger;
};

#define Log_Trace(...)    Logger::s_logger->trace(__VA_ARGS__)
#define Log_Info(...)     Logger::s_logger->info(__VA_ARGS__)
#define Log_Warn(...)     Logger::s_logger->warn(__VA_ARGS__)
#define Log_Error(...)    Logger::s_logger->error(__VA_ARGS__)
#define Log_Critical(...) Logger::s_logger->critical(__VA_ARGS__)

#define Log_Assert(x, ...) {if(!(x)){\
	Log_Critical("Assertion Failed: {0}", __VA_ARGS__);\
	__debugbreak();\
}}