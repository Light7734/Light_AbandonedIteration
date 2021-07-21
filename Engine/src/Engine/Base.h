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

#define LT_VERSION "0.7.0" 
///*** [  CHANGE_LOG  ] ***///
// --------------------------------------------------------------------
// Note: change log starts from 2021-07-21, the starting version is 
// 0.7.0, I came up with that version because of the engine's major
// features: 
//     projects: 'Engine', 'Sandbox', 'Mirror' + 0.3
//     graphics apis: 'OpenGL', 'DirectX11' + 0.2
//     platforms: 'Windows', 'Linux' + 0.2
// --------------------------------------------------------------------
// 
// 0.7.0: started the change log
// 
///*** [  CHANGE_LOG  ] ***///

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
	#define LT_CLIENT_ASSERT(x, ...) { if(!(x)) { LT_CLIENT_CRITICAL(__VA_ARGS__); __debugbreak(); } }

#elif defined(LIGHT_PLATFORM_LINUX)
	#define LT_CLIENT_ASSERT(x, ...) { if(!(x)) { LT_CLIENT_CRITICAL(__VA_ARGS__); __builtin_trap(); } }	
#endif