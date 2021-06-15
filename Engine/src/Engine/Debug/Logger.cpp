#include "ltpch.h"
#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

#include "Utility/Stringifier.h"

namespace Light {

	std::shared_ptr<spdlog::logger> Logger::s_EngineLogger = nullptr;
	std::shared_ptr<spdlog::logger> Logger::s_ClientLogger = nullptr;

	void Light::Logger::Initialize()
	{
		// set spdlog pattern
		spdlog::set_pattern("%^[%M:%S:%e] <%n>: %v%$");

		// create loggers
		s_EngineLogger = spdlog::stdout_color_mt("Engine");
		s_ClientLogger = spdlog::stdout_color_mt("Client");

		// set level
#if defined(LIGHT_DEBUG)
		s_EngineLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_level(spdlog::level::trace);
#elif defined (LIGHT_RELEASE)
		s_EngineLogger->set_level(spdlog::level::info);
		s_ClientLogger->set_level(spdlog::level::info);
#else
		s_EngineLogger->set_level(spdlog::level::off);
		s_ClientLogger->set_level(spdlog::level::off);
#endif


	}

	void Logger::LogDebugData()
	{
		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("Logger::");
		LT_ENGINE_INFO("        ClientLevel: {}", Stringifier::spdlogLevel(s_ClientLogger->level()));
		LT_ENGINE_INFO("        EngineLevel: {}", Stringifier::spdlogLevel(s_EngineLogger->level()));
		LT_ENGINE_INFO("        DefaultLevel: {}", Stringifier::spdlogLevel(spdlog::get_level()));
		LT_ENGINE_INFO("________________________________________");
	}

}