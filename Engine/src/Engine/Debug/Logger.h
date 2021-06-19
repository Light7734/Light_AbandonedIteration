#pragma once

#include "Base.h"

#include <spdlog/spdlog.h>

// LOGGER MACROS //

#define LT_LOG_FILE_LOCATION "Log.txt";

// File
#define LT_FILE_INFO(...)       ::Light::Logger::GetFileLogger()->log(spdlog::level::info    , __VA_ARGS__)
#define LT_FILE_WARN(...)       ::Light::Logger::GetFileLogger()->log(spdlog::level::warn    , __VA_ARGS__)
#define LT_FILE_ERROR(...)      ::Light::Logger::GetFileLogger()->log(spdlog::level::err     , __VA_ARGS__)
#define LT_FILE_CRITICAL(...)   ::Light::Logger::GetFileLogger()->log(spdlog::level::critical, __VA_ARGS__)

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

	// #todo: add a FileLogger
	class Logger
	{
	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger, s_ClientLogger, s_FileLogger;
		static std::string s_LogFilePath;

	public:
		Logger() = delete;

		static void Initialize();

		static inline std::shared_ptr<spdlog::logger> GetEngineLogger() { return s_EngineLogger; }
		static inline std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }
		static inline std::shared_ptr<spdlog::logger> GetFileLogger() { return s_FileLogger; }

		static void LogDebugData();
	};

}