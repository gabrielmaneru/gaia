#include "pch.h"
#include "logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>


void Logger::create()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_logger = spdlog::stdout_color_mt("gaia");
	s_logger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger> Logger::s_logger;
