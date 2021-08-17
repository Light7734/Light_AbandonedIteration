#include "ltpch.h"
#include "Stringifier.h"

#include "Graphics/GraphicsContext.h"

#include <glad/glad.h>

#include <vulkan/vulkan.h>

#include <spdlog/common.h>

namespace Light {

	//============================== OPENGL ==============================//
	std::string Stringifier::glDebugMsgSeverity(unsigned int severity)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_NOTIFICATION:    return "GL_DEBUG_SEVERITY_NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW:             return "GL_DEBUG_SEVERITY_LOW";
		case GL_DEBUG_SEVERITY_MEDIUM:          return "GL_DEBUG_SEVERITY_MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH:            return "GL_DEBUG_SEVERITY_HIGH";
		default:                                return "UNKNOWN";
		}
	}

	std::string Stringifier::glDebugMsgSource(unsigned int source)
	{
		switch (source)
		{
		case GL_DEBUG_SOURCE_API:                return "GL_DEBUG_SOURCE_API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:      return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER:    return "GL_DEBUG_SOURCE_SHADER_COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY:        return "GL_DEBUG_SOURCE_THIRD_PARTY";
		case GL_DEBUG_SOURCE_APPLICATION:        return "GL_DEBUG_SOURCE_APPLICATION";
		case GL_DEBUG_SOURCE_OTHER:              return "GL_DEBUG_SOURCE_OTHER";
		default:                                 return "UNKNOWN";
		}
	}

	std::string Stringifier::glDebugMsgType(unsigned int type)
	{
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:                  return "GL_DEBUG_TYPE_ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:    return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:     return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY:            return "GL_DEBUG_TYPE_PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE:            return "GL_DEBUG_TYPE_PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER:                 return "GL_DEBUG_TYPE_MARKER";
		case GL_DEBUG_TYPE_PUSH_GROUP:             return "GL_DEBUG_TYPE_PUSH_GROUP";
		case GL_DEBUG_TYPE_POP_GROUP:              return "GL_DEBUG_TYPE_POP_GROUP";
		case GL_DEBUG_TYPE_OTHER:                  return "GL_DEBUG_TYPE_OTHER";
		default:                                   return "UNKNOWN";
		}
	}

	std::string Stringifier::vkErrorCode(int errorCode)
	{
		switch (errorCode)
		{
			case VK_SUCCESS : return "VK_SUCCESS";
			case VK_NOT_READY : return "VK_NOT_READY";
			case VK_TIMEOUT : return "VK_TIMEOUT";
			case VK_EVENT_SET : return "VK_EVENT_SET";
			case VK_EVENT_RESET : return "VK_EVENT_RESET";
			case VK_INCOMPLETE : return "VK_INCOMPLETE";
			case VK_ERROR_OUT_OF_HOST_MEMORY : return "VK_ERROR_OUT_OF_HOST_MEMORY";
			case VK_ERROR_OUT_OF_DEVICE_MEMORY : return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
			case VK_ERROR_INITIALIZATION_FAILED : return "VK_ERROR_INITIALIZATION_FAILED";
			case VK_ERROR_DEVICE_LOST : return "VK_ERROR_DEVICE_LOST";
			case VK_ERROR_MEMORY_MAP_FAILED : return "VK_ERROR_MEMORY_MAP_FAILED";
			case VK_ERROR_LAYER_NOT_PRESENT : return "VK_ERROR_LAYER_NOT_PRESENT";
			case VK_ERROR_EXTENSION_NOT_PRESENT : return "VK_ERROR_EXTENSION_NOT_PRESENT";
			case VK_ERROR_FEATURE_NOT_PRESENT : return "VK_ERROR_FEATURE_NOT_PRESENT";
			case VK_ERROR_INCOMPATIBLE_DRIVER : return "VK_ERROR_INCOMPATIBLE_DRIVER";
			case VK_ERROR_TOO_MANY_OBJECTS : return "VK_ERROR_TOO_MANY_OBJECTS";
			case VK_ERROR_FORMAT_NOT_SUPPORTED : return "VK_ERROR_FORMAT_NOT_SUPPORTED";
			case VK_ERROR_SURFACE_LOST_KHR : return "VK_ERROR_SURFACE_LOST_KHR";
			case VK_SUBOPTIMAL_KHR : return "VK_SUBOPTIMAL_KHR";
			case VK_ERROR_OUT_OF_DATE_KHR : return "VK_ERROR_OUT_OF_DATE_KHR";
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR : return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR : return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
			case VK_ERROR_VALIDATION_FAILED_EXT : return "VK_ERROR_VALIDATION_FAILED_EXT";
			case VK_RESULT_MAX_ENUM: return "VK_RESULT_MAX_ENUM";
		}
	}

	//============================== OPENGL ==============================//

	//==================== SPDLOG ====================//
	std::string Stringifier::spdlogLevel(unsigned int level)
	{
		switch (level)
		{
		case SPDLOG_LEVEL_TRACE:       return "SPDLOG_LEVEL_TRACE";
		case SPDLOG_LEVEL_DEBUG:       return "SPDLOG_LEVEL_DEBUG";
		case SPDLOG_LEVEL_INFO:        return "SPDLOG_LEVEL_INFO";
		case SPDLOG_LEVEL_WARN:        return "SPDLOG_LEVEL_WARN";
		case SPDLOG_LEVEL_ERROR:       return "SPDLOG_LEVEL_ERROR";
		case SPDLOG_LEVEL_CRITICAL:    return "SPDLOG_LEVEL_CRITICAL";
		case SPDLOG_LEVEL_OFF:         return "SPDLOG_LEVEL_OFF";
		default:                       return "UNKNOWN";
		}
	}
	//==================== SPDLOG ====================//

	//==================== GRAPHICS_API ====================//
	std::string Stringifier::GraphicsAPIToString(GraphicsAPI api)
	{
		switch (api)
		{
		case Light::GraphicsAPI::Default:    return "Default";
		case Light::GraphicsAPI::OpenGL:     return "OpenGL";
		case Light::GraphicsAPI::DirectX:    return "DirectX";
		case Light::GraphicsAPI::Vulkan:     return "Vulkan";
		case Light::GraphicsAPI::Metal:      return "Metal";
		default:                             return "UNKNOWN";
		}
	}
	//==================== GRAPHICS_API ====================//

}