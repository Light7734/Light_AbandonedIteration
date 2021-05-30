#include "ltpch.h"
#include "glGraphicsContext.h"

// Required for forward declaration
#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"
#include "Graphics/Shader.h"
#include "Graphics/Buffers.h"
#include "Graphics/VertexLayout.h"
#include "UserInterface/UserInterface.h" 

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

		LT_ENGINE_INFO("glGraphicsContext:");
		LT_ENGINE_INFO("        Renderer: {}", glGetString(GL_RENDERER));
		LT_ENGINE_INFO("        Version: {}", glGetString(GL_VERSION));
	}

}