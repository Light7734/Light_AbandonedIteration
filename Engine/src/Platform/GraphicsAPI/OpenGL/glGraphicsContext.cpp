#include "ltpch.h"
#include "glGraphicsContext.h"

#include "Events/WindowEvents.h"

#include "Graphics/Blender.h" // required for forward declaration
#include "Graphics/Buffers.h" // required for forward declaration
#include "Graphics/Renderer.h" // required for forward declaration
#include "Graphics/RenderCommand.h" // required for forward declaration

#include "UserInterface/UserInterface.h" // required for forward declaration

#include "Utility/ResourceManager.h" // required for forward declaration

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Light {

	glGraphicsContext::glGraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		// set 'GraphicsAPI'
		m_GraphicsAPI = GraphicsAPI::OpenGL;

		// make context current
		glfwMakeContextCurrent(windowHandle);
		
		// load opengl (glad)
		LT_ENGINE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "glGraphicsContext::glGraphicsContext: failed to initialize opengl (glad)");

		SetDebugMessageCallback();
	}

	void glGraphicsContext::LogDebugData()
	{
		// #todo: log more information
		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("GraphicsContext::");
		LT_ENGINE_INFO("        API     : OpenGL");
		LT_ENGINE_INFO("        Version : {}", glGetString(GL_VERSION));
		LT_ENGINE_INFO("        Renderer: {}", glGetString(GL_RENDERER));
		LT_ENGINE_INFO("________________________________________");
	}

	void glGraphicsContext::SetDebugMessageCallback()
	{
		// determine log level
		// #todo: set filters from config.h
#if defined(LIGHT_DEBUG)
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr , GL_TRUE);

		GLuint ids[] =
		{
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
		                          const void* userParam) 
		{
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:
				throw glException(source, type, id, message);
				return;

			case GL_DEBUG_SEVERITY_MEDIUM: case  GL_DEBUG_SEVERITY_LOW:
				LT_ENGINE_WARN("glMessageCallback: Severity: {} :: Source: {} :: Type: {} :: ID: {}",
				               Stringifier::glDebugMsgSeverity(severity),
				               Stringifier::glDebugMsgSource(source),
				               Stringifier::glDebugMsgType(type),
				               id);
				LT_ENGINE_WARN("        {}", message);
				return;

			case GL_DEBUG_SEVERITY_NOTIFICATION:
				LT_ENGINE_TRACE("glMessageCallback: Severity: {} :: Source: {} :: Type: {} :: ID: {}",
				                Stringifier::glDebugMsgSeverity(severity),
				                Stringifier::glDebugMsgSource(source),
				                Stringifier::glDebugMsgType(type),
				                id);
				LT_ENGINE_TRACE("        {}", message);
				return;
			}
		}, nullptr);
	}

}