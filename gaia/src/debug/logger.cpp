#include "pch.h"
#include "logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>


void Log::create_logger()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_logger = spdlog::stdout_color_mt("Engine");
	s_logger->set_level(spdlog::level::trace);
}

void Log::Trace(const char * msg)
{
	Log::s_logger->trace(msg);
}

void Log::Info(const char* msg)
{
	Log::s_logger->info(msg);
}

void Log::Warn(const char* msg)
{
	Log::s_logger->warn(msg);
}

void Log::Error(const char* msg)
{
	Log::s_logger->error(msg);
}

void Log::Critical(const char* msg)
{
	Log::s_logger->critical(msg);
}

std::shared_ptr<spdlog::logger> Log::s_logger;
