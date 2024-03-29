#include "glGraphicsContext.hpp"

#include "Events/WindowEvents.hpp"
#include "Graphics/Blender.hpp"            // required for forward declaration
#include "Graphics/Buffers.hpp"            // required for forward declaration
#include "Graphics/RenderCommand.hpp"      // required for forward declaration
#include "Graphics/Renderer.hpp"           // required for forward declaration
#include "UserInterface/UserInterface.hpp" // required for forward declaration
#include "Utility/ResourceManager.hpp"     // required for forward declaration

#include <glad/glad.h>

#ifndef STOP_FUCKING_ORDERING_THESE_THE_WRONG_WAY_CLANG_FORMAT____
	#include <GLFW/glfw3.h>
#endif

namespace Light {

glGraphicsContext::glGraphicsContext(GLFWwindow* windowHandle)
    : m_WindowHandle(windowHandle)
{
	// set 'GraphicsAPI'
	m_GraphicsAPI = GraphicsAPI::OpenGL;

	// make context current
	glfwMakeContextCurrent(windowHandle);

	// load opengl (glad)
	ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize opengl (glad)");

	SetDebugMessageCallback();
}

void glGraphicsContext::LogDebugData()
{
	// #todo: log more information
	LOG(info, "________________________________________");
	LOG(info, "GraphicsContext::");
	LOG(info, "        API     : OpenGL");
	LOG(info, "        Version : {}", glGetString(GL_VERSION));
	LOG(info, "        Renderer: {}", glGetString(GL_RENDERER));
	LOG(info, "________________________________________");
}

void glGraphicsContext::SetDebugMessageCallback()
{
	// determine log level
	// #todo: set filters from config.h
#if defined(LIGHT_DEBUG)
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

	GLuint ids[] = {
		131185
	};
	glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, _countof(ids), ids, GL_FALSE);
#elif defined(LIGHT_RELEASE)
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_FALSE);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, nullptr, GL_TRUE);
#else // LIGHT_DIST
	return;
#endif

	/* setup message callback */
	glDebugMessageCallback([](unsigned int source, unsigned int type,
	                          unsigned int id, unsigned int severity,
	                          int length, const char* message,
	                          const void* userParam) {
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			// throw glException(source, type, id, message);
			return;

		case GL_DEBUG_SEVERITY_MEDIUM:
		case GL_DEBUG_SEVERITY_LOW:
			LOG(warn, "glMessageCallback: Severity: {} :: Source: {} :: Type: {} :: ID: {}",
			    Stringifier::glDebugMsgSeverity(severity),
			    Stringifier::glDebugMsgSource(source),
			    Stringifier::glDebugMsgType(type),
			    id);
			LOG(warn, "      {}", message);
			return;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
			LOG(trace, "Severity: {} :: Source: {} :: Type: {} :: ID: {}",
			    Stringifier::glDebugMsgSeverity(severity),
			    Stringifier::glDebugMsgSource(source),
			    Stringifier::glDebugMsgType(type),
			    id);
			LOG(trace, "        {}", message);
			return;
		}
	},
	                       nullptr);
}

} // namespace Light
