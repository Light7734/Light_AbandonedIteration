#pragma once

#ifndef LOGGER_H
	#include "Debug/Logger.h"
#endif

#include "Debug/Exceptions.h"

#include <memory>

#define LT_WIN(x) // Windows
#define LT_LIN(x) // Linux
#define LT_MAC(x) // Mac

#if defined(LIGHT_PLATFORM_WINDOWS)
	#define LT_BUILD_PLATFORM "Windows"
	#define LT_WIN(x) x
#elif defined(LIGHT_PLATFORM_LINUX)
	#error "Unsupported platform: UNIX"
	#define LT_LIN(x)
#elif defined(LIGHT_PLATFORM_MAC)
	#error "Unsupported platform: MAC"
	#define LT_MAC(x) x
#else
	#error "Unsupported platform: Unknown"
#endif

#define BIT(x) 1 << x

// #todo: log to file in distribution builds
#define LT_ENGINE_ASSERT(x, ...) { if(!(x)) { LT_ENGINE_CRITICAL(__VA_ARGS__); __debugbreak(); throw ::Light::FailedAssertion(__FILE__, __LINE__); } }
#define LT_CLIENT_ASSERT(x, ...) { if(!(x)) { LT_CLIENT_CRITICAL(__VA_ARGS__); __debugbreak(); } }