#pragma once

#include "Base.h"

#include <spdlog/spdlog.h>

// LOGGER MACROS //
#ifndef LIGHT_DIST
	// Engine
	#define LT_ENGINE_TRACE(...)    ::Light::Logger::GetEngineLogger()->log(spdlog::level::trace   , __VA_ARGS__)
	#define LT_ENGINE_INFO(...)     ::Light::Logger::GetEngineLogger()->log(spdlog::level::info    , __VA_ARGS__)
	#define LT_ENGINE_WARN(...)     ::Light::Logger::GetEngineLogger()->log(spdlog::level::warn    , __VA_ARGS__)
	#define LT_ENGINE_ERROR(...)    ::Light::Logger::GetEngineLogger()->log(spdlog::level::err     , __VA_ARGS__)
	#define LT_ENGINE_CRITICAL(...) ::Light::Logger::GetEngineLogger()->log(spdlog::level::critical, __VA_ARGS__)
	
	// Client
	#define LT_CLIENT_TRACE(...)    ::Light::Logger::GetClientLogger()->log(spdlog::level::trace   , __VA_ARGS__)
	#define LT_CLIENT_INFO(...)     ::Light::Logger::GetClientLogger()->log(spdlog::level::info    , __VA_ARGS__)
	#define LT_CLIENT_WARN(...)     ::Light::Logger::GetClientLogger()->log(spdlog::level::warn    , __VA_ARGS__)
	#define LT_CLIENT_ERROR(...)    ::Light::Logger::GetClientLogger()->log(spdlog::level::err     , __VA_ARGS__)
	#define LT_CLIENT_CRITICAL(...) ::Light::Logger::GetClientLogger()->log(spdlog::level::critical, __VA_ARGS__)
#else
	#define LT_ENGINE_TRACE(...)
	#define LT_ENGINE_INFO(...)
	#define LT_ENGINE_WARN(...)
	#define LT_ENGINE_ERROR(...)
	#define LT_ENGINE_CRITICAL(...)
	#define LT_CLIENT_TRACE(...)
	#define LT_CLIENT_INFO(...)
	#define LT_CLIENT_WARN(...)
	#define LT_CLIENT_ERROR(...)
	#define LT_CLIENT_CRITICAL(...)
#endif

namespace Light {

	class Logger
	{
	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger, s_ClientLogger;

	public:
		Logger() = delete;

		static void Initialize();

		static inline std::shared_ptr<spdlog::logger> GetEngineLogger() { return s_EngineLogger; }
		static inline std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }
	};

}