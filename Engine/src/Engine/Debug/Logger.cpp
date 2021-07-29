#include "ltpch.h"
#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Light {

	Logger* Logger::s_Context = nullptr;

	Scope<Logger> Logger::Create()
	{
		return MakeScope<Logger>(new Logger());
	}

	Logger::Logger()
		: m_EngineLogger(nullptr),
		  m_ClientLogger(nullptr),
		  m_FileLogger(nullptr),
		  m_LogFilePath(LT_LOG_FILE_LOCATION)
	{
		LT_ENGINE_ASSERT(!s_Context, "Logger::Logger: an instance of 'Logger' already exists, do not construct this class!");
		s_Context = this;

		// set spdlog pattern
#if   defined(LIGHT_PLATFORM_WINDOWS)
		spdlog::set_pattern("%^[%M:%S:%e] <%n>: %v%$");
#elif defined(LIGHT_PLATFORM_LINUX)
		spdlog::set_pattern("%^{%l} - [%M:%S:%e] <%n>: %v%$");
#endif
		// create loggers
#ifndef LIGHT_DIST
		m_EngineLogger = spdlog::stdout_color_mt("Engine");
		m_ClientLogger = spdlog::stdout_color_mt("Client");
#endif
		m_FileLogger = spdlog::basic_logger_mt("File", m_LogFilePath);
		m_FileLogger->set_pattern("%^[%M:%S:%e] <%l>: %v%$");

		// set level
#if   defined(LIGHT_DEBUG)
		m_EngineLogger->set_level(spdlog::level::trace);
		m_ClientLogger->set_level(spdlog::level::trace);
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
		LT_ENGINE_INFO("        ClientLevel : {}", Stringifier::spdlogLevel(m_ClientLogger->level()));
		LT_ENGINE_INFO("        EngineLevel : {}", Stringifier::spdlogLevel(m_EngineLogger->level()));
		LT_ENGINE_INFO("        FileLevel   : {}", Stringifier::spdlogLevel(m_FileLogger->level()));
		LT_ENGINE_INFO("        DefaultLevel: {}", Stringifier::spdlogLevel(spdlog::get_level()));
		LT_ENGINE_INFO("________________________________________");
	}

}