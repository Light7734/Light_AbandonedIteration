#pragma once

#include "Core/Logger.h"

#if defined(LIGHT_PLATFORM_WINDOWS)
	#define LT_BUILD_PLATFORM "Windows"
#elif defined(LT_PLATFORM_LINUX)
	#error "Unsupported platform: UNIX"
#else
	#error "Unsupported platform: Unknown"
#endif


#define BIT(x) 1 << x

#define LT_ENGINE_ASSERT(x, ...) { if(!(x)) { LT_ENGINE_CRITICAL(__VA_ARGS__); __debugbreak(); } }
#define LT_CLIENT_ASSERT(x, ...) { if(!(x)) { LT_CLIENT_CRITICAL(__VA_ARGS__); __debugbreak(); } }

