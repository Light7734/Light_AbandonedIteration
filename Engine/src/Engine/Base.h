#pragma once

#ifndef LOGGER_H
	#include "Debug/Logger.h"
#endif

#include "Debug/Exceptions.h"
#include "Utility/Stringifier.h"

#include <memory>

#define LT_WIN(x) // windows
#define LT_LIN(x) // linux
#define LT_MAC(x) // mac

// #todo: figure out a proper way to give version numbers
#define LT_VERSION "0.5.1" 

#if defined(LIGHT_PLATFORM_WINDOWS)
	#define LT_BUILD_PLATFORM "Windows"
	#define LT_WIN(x) x
	
#elif defined(LIGHT_PLATFORM_LINUX)
	#define LT_BUILD_PLATFORM "Linux"
	#define LT_LIN(x) x
	
#elif defined(LIGHT_PLATFORM_MAC)
	#error "Unsupported platform: MAC"
	#define LT_MAC(x) x
	
#else
	#error "Unsupported platform: Unknown"

#endif

#define BIT(x) 1 << x

// #todo: log to file in distribution builds
#if defined(LIGHT_PLATFORM_WINDOWS)
	#define LT_ENGINE_ASSERT(x, ...) { if(!(x)) { LT_ENGINE_CRITICAL(__VA_ARGS__); __debugbreak(); throw ::Light::FailedAssertion(__FILE__, __LINE__); } }
	#define LT_CLIENT_ASSERT(x, ...) { if(!(x)) { LT_CLIENT_CRITICAL(__VA_ARGS__); __debugbreak(); } }

#elif defined(LIGHT_PLATFORM_LINUX)
	#define LT_ENGINE_ASSERT(x, ...) { if(!(x)) { LT_ENGINE_CRITICAL(__VA_ARGS__); __builtin_trap(); throw ::Light::FailedAssertion(__FILE__, __LINE__); } }
	#define LT_CLIENT_ASSERT(x, ...) { if(!(x)) { LT_CLIENT_CRITICAL(__VA_ARGS__); __builtin_trap(); } }	
#endif