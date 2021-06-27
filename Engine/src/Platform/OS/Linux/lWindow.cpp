#include "ltpch.h"
#include "lWindow.h"

#include "Events/Event.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/WindowEvents.h"

#include "Graphics/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Light {
	
	Window* Window::Create(std::function<void(Event&)> callback)
	{
		return new lWindow(callback);
	}
	
	lWindow::lWindow(std::function<void(Event&)> callback)
		: m_EventCallback(callback)
	{
		// init glfw
		LT_ENGINE_ASSERT(glfwInit(), "lWindow::lWindow: failed to initialize glfw");
		
		// create window
		glfwWindowHint(GLFW_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		
		m_Handle = glfwCreateWindow(1u, 1u, "", nullptr, nullptr);
		LT_ENGINE_ASSERT(m_Handle, "lWindow::lWindow: failed to create glfw window");
		
		// manage events
		glfwSetWindowUserPointer(m_Handle, &m_EventCallback);
		BindGlfwEvents();
		
		// create graphics context
		m_GraphicsContext = std::unique_ptr<GraphicsContext>(GraphicsContext::Create(GraphicsAPI::OpenGL, m_Handle));
		LT_ENGINE_ASSERT(m_GraphicsContext, "lWindow::lWindow: failed to create graphics context");
	}
	
	lWindow::~lWindow()
	{
		glfwDestroyWindow(m_Handle);
	}
	
	void lWindow::SetProperties(const WindowProperties& properties)
	{
		m_Properties = properties;
		
		glfwSetWindowSize(m_Handle, properties.size.x, properties.size.y);
		glfwSetWindowTitle(m_Handle, properties.title.c_str());
		glfwSwapInterval(static_cast<int>(properties.vsync));
	}
	
	void lWindow::SetTitle(const std::string& title)
	{
		m_Properties.title = title;
		
		glfwSetWindowTitle(m_Handle, title.c_str());
	}
	
	void lWindow::SetSize(const glm::uvec2& size, bool add/*= false*/)
	{
		m_Properties.size.x = size.x == 0u ? m_Properties.size.x : add  ? m_Properties.size.x + size.x : size.x;
		m_Properties.size.y = size.y == 0u ? m_Properties.size.y : add  ? m_Properties.size.y + size.y : size.y;
 
		
		glfwSetWindowSize(m_Handle, size.x, size.y);
	}
	
	void lWindow::SetVSync(bool vsync, bool toggle/*= false*/)
	{
		m_Properties.vsync = toggle ? !m_Properties.vsync : vsync;
		
		glfwSwapInterval(m_Properties.vsync);
	}
	
	void lWindow::SetVisibility(bool visible, bool toggle)
	{
		m_Properties.visible = toggle ? !m_Properties.visible : visible;
		
		if(m_Properties.visible)
			glfwShowWindow(m_Handle);
		else
			glfwHideWindow(m_Handle);
	}
	
	void lWindow::BindGlfwEvents()
	{
		//** mouse events **//
		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xpos, double ypos)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			
			MouseMovedEvent event(xpos, ypos);
			callback(event);
		});
		
		glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
		
			if(action == GLFW_PRESS)
			{
				ButtonPressedEvent event(button);
				callback(event);
			}
			else
			{
				ButtonReleasedEvent	event(button);
				callback(event);
			}
		});
		
		glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			WheelScrolledEvent event(yoffset);
			callback(event);
		});
		
		//** keyboard events **//
		glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
		
			if(action == GLFW_PRESS)
			{
				KeyPressedEvent event(key);
				callback(event);
			}
			else
			{
				KeyReleasedEvent event(key);
				callback(event);
			}
		});
		
		//** window events **//
		glfwSetWindowPosCallback(m_Handle, [](GLFWwindow* window, int xpos, int ypos)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			WindowMovedEvent event(xpos, ypos);
			
			callback(event);
		});

		glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height) 
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			WindowResizedEvent event(width, height);
			
			callback(event);
		});

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			WindowClosedEvent event;
			
			callback(event);
		});

		glfwSetWindowFocusCallback(m_Handle, [](GLFWwindow* window, int focus)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			if(focus == GLFW_TRUE)
			{
				WindowGainFocusEvent event;
				callback(event);
			}
			else
			{
				WindowLostFocusEvent event;
				callback(event);
			}
		});
	}

}