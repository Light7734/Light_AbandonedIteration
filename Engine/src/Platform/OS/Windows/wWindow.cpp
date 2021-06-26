#include "ltpch.h"
#include "wWindow.h"

#include "Events/Event.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/WindowEvents.h"

#include "Graphics/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Light {

	Window* Window::Create(std::function<void(Event&)> callback)
	{
		return new wWindow(callback);
	}

	wWindow::wWindow(std::function<void(Event&)> callback)
		: m_EventCallback(callback)
	{
		// init glfw
		LT_ENGINE_ASSERT(glfwInit(), "wWindow::wWindow: failed to initialize glfw");

		// create window
	
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Handle = glfwCreateWindow(800u, 600u, "", nullptr, nullptr);

		LT_ENGINE_ASSERT(m_Handle, "wWindow::wWindow: glfwCreateWindow: failed to create glfw window");

		// manage events
		glfwSetWindowUserPointer(m_Handle, &m_EventCallback);
		BindGlfwEvents();

		// create graphics context
		m_GraphicsContext = std::unique_ptr<GraphicsContext>(GraphicsContext::Create(GraphicsAPI::OpenGL, m_Handle));
		LT_ENGINE_ASSERT(m_GraphicsContext, "wWindow::wWindow: failed to create graphics context");
	}

	wWindow::~wWindow()
	{
		glfwDestroyWindow(m_Handle);
	}

	void wWindow::SetProperties(const WindowProperties& properties)
	{
		m_Properties = properties;

		glfwSetWindowSize(m_Handle, properties.size.x, properties.size.y); // #todo: check if this triggers an event
		glfwSetWindowTitle(m_Handle, properties.title.c_str());
		glfwSwapInterval((int)properties.vsync);
	}

	void wWindow::SetVisibility(bool visible, bool toggle)
	{
		m_Properties.visible = toggle ? !m_Properties.visible : visible;

		if (m_Properties.visible)
			glfwShowWindow(m_Handle);
		else
			glfwHideWindow(m_Handle);
	}

	void wWindow::PollEvents()
	{
		glfwPollEvents();
	}

	void wWindow::OnEvent(const Event& event)
	{
		switch (event.GetEventType())
		{
		case EventType::WindowClosed:
			b_Closed = true;
			break;

		case EventType::WindowResized:
			m_GraphicsContext->OnWindowResize((const WindowResizedEvent&)event);
			break;
		}
	}

	void wWindow::SetTitle(const std::string& title)
	{
		m_Properties.title = title;

		glfwSetWindowTitle(m_Handle, m_Properties.title.c_str());
	}

	void wWindow::SetVSync(bool vsync, bool toggle /*= false*/)
	{
		m_Properties.vsync = toggle ? !m_Properties.vsync : vsync;

		glfwSwapInterval(m_Properties.vsync);
	}

	void wWindow::SetSize(const glm::uvec2& size, bool add /*= false*/)
	{
		m_Properties.size.x = size.x == 0u ? m_Properties.size.x : add ? m_Properties.size.x + size.x : size.x;
		m_Properties.size.y = size.y == 0u ? m_Properties.size.y : add ? m_Properties.size.y + size.y : size.y;

		glfwSetWindowSize(m_Handle, m_Properties.size.x, m_Properties.size.y);
	}

	void wWindow::BindGlfwEvents()
	{
		// Mouse Events //
		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xpos, double ypos)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event(xpos, ypos);
			callback(event);
		});

		glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods) 
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS)
			{
				ButtonPressedEvent event(button);
				callback(event);
			}
	
			else
			{		
				ButtonReleasedEvent event(button);
				callback(event);
			}

		});

		glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			
			WheelScrolledEvent event(yoffset);
			callback(event);
		});

		// Keyboard Events //
		glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS)
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

		// Window Events //
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