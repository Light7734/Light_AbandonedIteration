#include "ltpch.h"
#include "Exceptions.h"

#include "Utility/Stringifier.h"

#include <glad/glad.h>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

namespace Light {

	glException::glException(unsigned int source, unsigned int type, unsigned int id, const char* msg)
	{
		LT_ENGINE_CRITICAL("________________________________________");
		LT_ENGINE_CRITICAL("glException::glException::");
		LT_ENGINE_CRITICAL("        Severity: {}", Stringifier::glDebugMsgSeverity(GL_DEBUG_SEVERITY_HIGH));
		LT_ENGINE_CRITICAL("        Source  : {}", Stringifier::glDebugMsgSource(source));
		LT_ENGINE_CRITICAL("        Type    : {}", Stringifier::glDebugMsgType(type));
		LT_ENGINE_CRITICAL("        ID      : {}", id);
		LT_ENGINE_CRITICAL("        Vendor  : {}", glGetString(GL_VENDOR));
		LT_ENGINE_CRITICAL("        Renderer: {}", glGetString(GL_RENDERER));
		LT_ENGINE_CRITICAL("        Version : {}", glGetString(GL_VERSION));
		LT_ENGINE_CRITICAL("        SVersion: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
		LT_ENGINE_CRITICAL("        {}", msg);

		LT_ENGINE_CRITICAL("________________________________________");
	}

	LT_WIN(
	dxException::dxException(long hr, const char* file, int line)
	{
		char* message;
		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		               nullptr, hr,
		               MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		               (LPSTR)(&message), NULL, nullptr);

		// #todo: format better
		LT_ENGINE_CRITICAL("________________________________________");
		LT_ENGINE_CRITICAL("dxException::dxException::");
		LT_ENGINE_CRITICAL("        File: {}, Line: {}", file, line);
		LT_ENGINE_CRITICAL("        {}", message);
		LT_ENGINE_CRITICAL("________________________________________");

		LocalFree(message);
	})

}