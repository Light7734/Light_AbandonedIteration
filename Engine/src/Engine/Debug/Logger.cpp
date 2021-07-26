#include "ltpch.h"
#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Light {

	Ref<spdlog::logger> Logger::s_EngineLogger = nullptr;
	Ref<spdlog::logger> Logger::s_ClientLogger = nullptr;
	Ref<spdlog::logger> Logger::s_FileLogger = nullptr;

	std::string Logger::s_LogFilePath = LT_LOG_FILE_LOCATION;

	void Light::Logger::Initialize()
	{
		// set spdlog pattern
#if   defined(LIGHT_PLATFORM_WINDOWS)
		spdlog::set_pattern("%^[%M:%S:%e] <%n>: %v%$");
#elif defined(LIGHT_PLATFORM_LINUX)
		spdlog::set_pattern("%^{%l} - [%M:%S:%e] <%n>: %v%$");
#endif
		// create loggers
#ifndef LIGHT_DIST
		s_EngineLogger = spdlog::stdout_color_mt("Engine");
		s_ClientLogger = spdlog::stdout_color_mt("Client");
#endif
		s_FileLogger = spdlog::basic_logger_mt("File", s_LogFilePath);
		s_FileLogger->set_pattern("%^[%M:%S:%e] <%l>: %v%$");

		// set level
#if   defined(LIGHT_DEBUG)
		s_EngineLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_level(spdlog::level::trace);
#elif defined (LIGHT_RELEASE)
		s_EngineLogger->set_level(spdlog::level::info);
		s_ClientLogger->set_level(spdlog::level::info);
#endif
	}

	void Logger::LogDebugData()
	{
		// #todo: improve
		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("Logger::");
		LT_ENGINE_INFO("        ClientLevel : {}", Stringifier::spdlogLevel(s_ClientLogger->level()));
		LT_ENGINE_INFO("        EngineLevel : {}", Stringifier::spdlogLevel(s_EngineLogger->level()));
		LT_ENGINE_INFO("        FileLevel   : {}", Stringifier::spdlogLevel(s_FileLogger->level()));
		LT_ENGINE_INFO("        DefaultLevel: {}", Stringifier::spdlogLevel(spdlog::get_level()));
		LT_ENGINE_INFO("________________________________________");
	}

}