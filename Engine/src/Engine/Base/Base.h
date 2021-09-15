#pragma once

#include <memory>

namespace Light {

	// Ref (Ref)
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	constexpr Ref<T> MakeRef(T* rawPointer)
	{
		return std::shared_ptr<T>(rawPointer);
	}

	// Scope (std::unique_ptr)
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename... Args>
	constexpr std::unique_ptr<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	constexpr std::unique_ptr<T> MakeScope(T* rawPointer)
	{
		return std::unique_ptr<T>(rawPointer);
	}

}

//========== PLATFORM ==========//
#define LT_WIN(x) // windows
#define LT_LIN(x) // linux
#define LT_MAC(x) // mac

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
//========== PLATFORM ==========//

//====================================================================== OPERATIONS ======================================================================//
/* assertions */
#define LT_ENGINE_ASSERT(x, ...) { if(!(x)) { LT_ENGINE_CRITICAL(__VA_ARGS__); LT_DEBUG_TRAP(); throw ::Light::FailedEngineAssertion(__FILE__, __LINE__); } }
#define LT_CLIENT_ASSERT(x, ...) { if(!(x)) { LT_CLIENT_CRITICAL(__VA_ARGS__); LT_DEBUG_TRAP(); throw ::Light::FailedClientAssertion(__FILE__, __LINE__); } }

/* bit-wise */
#define BIT(x) 1 << x

/* token */
#define LT_PAIR_TOKEN_VALUE_TO_NAME(token) { token, #token }
#define LT_PAIR_TOKEN_NAME_TO_VALUE(token) { #token, token }
#define LT_TOKEN_NAME(token) #token
//====================================================================== OPERATIONS ======================================================================//

//========== ESSENTIAL_HEADERS ==========//
/* config */
#ifndef LIGHT_CONFIG_H
	#include "Base/Config.h"
#endif

/* debug */
#ifndef LIGHT_LOGGER_H
	#include "Debug/Logger.h"
#endif
#include "Debug/Exceptions.h"

/* portables */
#ifndef LIGHT_DEBUG_TRAP_H
	#include "Base/Portables/DebugTrap.h"
#endif

/* utility */
#ifndef LIGHT_STRINGIFIER_H
	#include "Utility/Stringifier.h"
#endif
//========== ESSENTIAL_HEADERS ==========//