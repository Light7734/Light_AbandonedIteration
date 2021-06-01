#include "ltpch.h"
#include "glGraphicsContext.h"

// Required for forward declaration
#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"
#include "Graphics/Shader.h"
#include "Graphics/Buffers.h"
#include "Graphics/VertexLayout.h"
#include "UserInterface/UserInterface.h" 

#include "Events/WindowEvents.h"

#include "Utility/Stringifier.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Light {

	glGraphicsContext::glGraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		m_GraphicsAPI = GraphicsAPI::OpenGL;

		glfwMakeContextCurrent(windowHandle);
		LT_ENGINE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress),
		                 "glGraphicsContext::glGraphicsContext: gladLoadGLLoader: failed to initialize opengl context");

		SetDebugMessageCallback();
	}

	void glGraphicsContext::OnWindowResize(const WindowResizedEvent& event)
	{
		glViewport(0, 0, event.GetSize().x, event.GetSize().y);
	}

	void glGraphicsContext::LogDebugData()
	{
		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("GraphicsContext::");
		LT_ENGINE_INFO("        API     : OpenGL");
		LT_ENGINE_INFO("        Version : {}", glGetString(GL_VERSION));
		LT_ENGINE_INFO("        Renderer: {}", glGetString(GL_RENDERER));
		LT_ENGINE_INFO("________________________________________");
	}

	void glGraphicsContext::SetDebugMessageCallback()
	{
#if defined(LT_DEBUG)
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#elif defined(LT_RELEASE)
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_FALSE);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
#else // LT_DIST
		return;
#endif

		glDebugMessageCallback([](unsigned int source, unsigned int type,
		                          unsigned int id, unsigned int severity,
		                          int length, const char* message,
		                          const void* userParam) 
		{
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:
				LT_ENGINE_CRITICAL("glMessageCallback: Severity: {} :: Source: {} :: Type: {} :: ID: {}",
				                   Stringifier::glDebugMsgSeverity(severity),
				                   Stringifier::glDebugMsgSource(source),
				                   Stringifier::glDebugMsgType(type),
				                   id);
				LT_ENGINE_CRITICAL("        {}", message);
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