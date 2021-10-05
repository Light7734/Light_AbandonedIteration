#pragma once
#ifndef LIGHT_LOGGER_H
#define LIGHT_LOGGER_H

#include "Base/Base.h"

#include <spdlog/spdlog.h>

// LOGGER MACROS //

#define LT_LOG_FILE_LOCATION "Logs/Logger.txt"

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

	// #todo: extend
	class Logger /* singleton */
	{
	private:
		static Logger* s_Context;

	private:
		Ref<spdlog::logger> m_EngineLogger, m_ClientLogger, m_FileLogger;
		std::string m_LogFilePath;

	public:
		static Scope<Logger> Create();

		static inline Ref<spdlog::logger> GetEngineLogger() { return s_Context->m_EngineLogger; }
		static inline Ref<spdlog::logger> GetClientLogger() { return s_Context->m_ClientLogger; }
		static inline Ref<spdlog::logger> GetFileLogger() { return s_Context->m_FileLogger; }

		void LogDebugData();

	private:
		Logger();
	};

}

#endif