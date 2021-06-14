#include "ltpch.h"
#include "wWindow.h"

#include "Events/Event.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/WindowEvents.h"

#include "Graphics/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Light {

	Window* Window::Create(const WindowProperties& properties, std::function<void(Event&)> callback)
	{
		return new wWindow(properties, callback);
	}

	wWindow::wWindow(std::function<void(Event&)> callback)
		: m_EventCallback(callback)
	{
		LT_ENGINE_ASSERT(glfwInit(), "wWindow::wWindow: glfwInit: failed to initialize glfw");

		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		m_Handle = glfwCreateWindow(1u, 1u, "", nullptr, nullptr);
		LT_ENGINE_ASSERT(m_Handle, "wWindow::wWindow: glfwCreateWindow: failed to create glfw window");

		glfwSetWindowUserPointer(m_Handle, &m_EventCallback);
		BindGlfwEvents();

		m_GraphicsContext = std::unique_ptr<GraphicsContext>(GraphicsContext::Create(GraphicsAPI::OpenGL, m_Handle));
		LT_ENGINE_ASSERT(m_GraphicsContext, "wWindow::wWindow: graphics context creation failed");
	}

	wWindow::~wWindow()
	{
		glfwDestroyWindow(m_Handle);
	}

	void wWindow::SetProperties(const WindowProperties& properties)
	{
		m_Properties = properties;

		glfwSetWindowSize(m_Handle, properties.width, properties.height);
		glfwSetWindowTitle(m_Handle, properties.title.c_str());
		glfwSwapInterval((int)properties.vsync);
	}

	void wWindow::SetVisible(bool visible)
	{
		if (visible)
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
			b_Open = false;
		case EventType::WindowResized:
			m_GraphicsContext->OnWindowResize((const WindowResizedEvent&)event);
		}
	}

	unsigned int wWindow::GetWidth()
	{
		return m_Properties.width;
	}

	unsigned int wWindow::GetHeight()
	{
		return m_Properties.height;
	}

	void wWindow::BindGlfwEvents()
	{
		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xpos, double ypos)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			callback(MouseMovedEvent(xpos, ypos));
		});

		glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods) 
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS)
				callback(ButtonPressedEvent(button));
			else
				callback(ButtonReleasedEvent(button));
		});

		glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			callback(WheelScrolledEvent(yoffset));
		});

		glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS)
				callback(KeyPressedEvent(key));
			else
				callback(KeyReleasedEvent(key));
		});

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window) 
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			callback(WindowClosedEvent());
		});

		glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height) 
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			callback(WindowResizedEvent(width, height));
		});

		glfwSetWindowPosCallback(m_Handle, [](GLFWwindow* window, int xpos, int ypos)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			callback(WindowMovedEvent(xpos, ypos));
		});

		glfwSetWindowFocusCallback(m_Handle, [](GLFWwindow* window, int focus)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			if(focus == GLFW_TRUE)
				callback(WindowGainFocusEvent());
			else
				callback(WindowLostFocusEvent());
			});
	}

}