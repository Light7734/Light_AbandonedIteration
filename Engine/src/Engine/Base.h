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