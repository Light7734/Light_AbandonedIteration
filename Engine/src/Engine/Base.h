#pragma once

#ifndef LOGGER_H
	#include "Debug/Logger.h"
#endif

#include "Debug/Exceptions.h"
#include "Utility/Stringifier.h"

#include <memory>


// version
#define LT_VERSION "0.7.5b"
///*** [  CHANGE_LOG  ] ***///
// --------------------------------------------------------------------
// Note: change log starts from 2021-07-21, the starting version is 0.7.0a,
// I came up with that version because of:
//     projects: 'Engine', 'Sandbox', 'Mirror' [+0.3]
//     graphics apis: 'OpenGL', 'DirectX11'    [+0.2]
//     platforms: 'Windows', 'Linux'           [+0.2]
// --------------------------------------------------------------------
// 
// 
// 0.7.0a: started the change log
//
// 0.7.1a: [ LT_BREAK ]
//     - Added the 'LT_BERAK' macro, a portable debug-trap
// 
// 0.7.2a: [ Failed engine/client assertion ]
//     - Separated 'FailedAssertion' into 'FailedEngineAssertion' and 'FailedClientAssertion'
//     - Minor adjustment to the change log
// 
// 0.7.3a: [ Layer Improvements ]
//     - Added 'Layer::OnEvent()', 'Layer' now handles an event by itself and doesn't need another class to determine the event's type
//     
//     - Added reverse iterators 'rend()' and 'rbegin()' to 'LayerStack'
//     
//     - Removed 'LayerStack::On*()', 'LayerStack'
//     
//     - 'Layer::On*Event()' are now protected and called by 'Layer::OnEvent()'
//     
//     - 'Application' now handles iterating through the 'Layer's and calling the update / on * functions
//     
//     - Fixed a typo where in 'Mirror' where the name of the 'MirrorLayer' was "SandboxLayer" instead of "MirrorLayer"
// 
// 0.7.4a: [ Input ]
//     - Added 'Input'
//     - - Added <InputCodes>
//     - The 'MirrorLayer''s ImGuiWindow, "GameView" will not receive/react to input events if the window is not focused
// 
//  0.7.4b [ Maintenance ]
//      - Added 'Get*Ref()' to 'dxSharedContext'
//      
//      - Fixed 'dxFramebuffer::Resize' not resizing : /
//      - Fixed 'dxFrameBuffer::BindAsTarget' not setting the viewport
//      - Fixed 'dxRenderCommand::SetViewport()' not resizing the swapchain's buffer
//      
//      - Improved 'dxGraphicsContext''s debug interface
//      
//      - Removed most of the 'ComPtr's in 'dxGraphicsContext', they can be accessed with the 'm_SharedContext'
// 
///*** [  CHANGE_LOG  ] ***///

// platform	
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

// operations
#define BIT(x) 1 << x

// assertions
// #todo: log to file in distribution builds
#define LT_ENGINE_ASSERT(x, ...) { if(!(x)) { LT_ENGINE_CRITICAL(__VA_ARGS__); LT_BREAK(); throw ::Light::FailedEngineAssertion(__FILE__, __LINE__); } }
#define LT_CLIENT_ASSERT(x, ...) { if(!(x)) { LT_CLIENT_CRITICAL(__VA_ARGS__); LT_BREAK(); throw ::Light::FailedClientAssertion(__FILE__, __LINE__); } } }


///*** [  PORTABLES  ] ***///
//** PORTABLE_DEBUG_BREAK **//
// copied from: https://github.com/nemequ/portable-snippets/tree/master/debug-trap
#if defined(__has_builtin) && !defined(__ibmxl__)
	#if __has_builtin(__builtin_debugtrap)
		#define LT_BREAK() __builtin_debugtrap()

	#elif __has_builtin(__debugbreak)
		#define LT_BREAK() __debugbreak()

	#endif
#endif

#if !defined(LT_BREAK)
	#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
		#define LT_BREAK() __debugbreak()

	#elif defined(__ARMCC_VERSION)
		#define LT_BREAK() __breakpoint(42)

	#elif defined(__ibmxl__) || defined(__xlC__)
		#include <builtins.h>
		#define LT_BREAK() __trap(42)

	#elif defined(__DMC__) && defined(_M_IX86)
		static inline void LT_BREAK(void) { __asm int 3h; }

	#elif defined(__i386__) || defined(__x86_64__)
		static inline void LT_BREAK(void) { __asm__ __volatile__("int3"); }

	#elif defined(__thumb__)
		static inline void LT_BREAK(void) { __asm__ __volatile__(".inst 0xde01"); }

	#elif defined(__aarch64__)
		static inline void LT_BREAK(void) { __asm__ __volatile__(".inst 0xd4200000"); }

	#elif defined(__arm__)
		static inline void LT_BREAK(void) { __asm__ __volatile__(".inst 0xe7f001f0"); }

	#elif defined (__alpha__) && !defined(__osf__)
		static inline void LT_BREAK(void) { __asm__ __volatile__("bpt"); }

	#elif defined(_54_)
		static inline void LT_BREAK(void) { __asm__ __volatile__("ESTOP"); }

	#elif defined(_55_)
		static inline void LT_BREAK(void) { __asm__ __volatile__(";\n .if (.MNEMONIC)\n ESTOP_1\n .else\n ESTOP_1()\n .endif\n NOP"); }

	#elif defined(_64P_)
		static inline void LT_BREAK(void) { __asm__ __volatile__("SWBP 0"); }

	#elif defined(_6x_)
		static inline void LT_BREAK(void) { __asm__ __volatile__("NOP\n .word 0x10000000"); }

	#elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ == 0) && defined(__GNUC__)
		#define LT_BREAK() __builtin_trap()

	#else
		#include <signal.h>

	#if defined(SIGTRAP)
		#define LT_BREAK() raise(SIGTRAP)

	#else
		#define LT_BREAK() raise(SIGABRT)

	#endif
	#endif
#endif

#if !defined(LT_BREAK)
	#define LT_BERAK LT_ENGINE_WARN("Unable to break!, LT_BREAK macro is undefined")
#endif

//** PORTABLE_DEBUG_BREAK **//
///*** [  PORTABLES  ] ***///

