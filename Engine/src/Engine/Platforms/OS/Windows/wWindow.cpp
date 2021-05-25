#include "wWindow.h"

#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"

namespace Light {

	Window* Window::Create(const WindowProperties& properties, std::function<void(Event&)> callback)
	{
		return new wWindow(properties, callback);
	}

	wWindow::wWindow(const WindowProperties& properties, std::function<void(Event&)> callback)
		: m_Properties(properties), m_EventCallback(callback)
	{
		if (!glfwInit()) __debugbreak();

		m_Handle = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_Handle);
		glfwSetWindowUserPointer(m_Handle, &m_EventCallback);

		BindGlfwEvents();
	}

	wWindow::~wWindow()
	{
		glfwDestroyWindow(m_Handle);
	}

	void wWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Handle);
	}

	void wWindow::OnEvent(const Event& event)
	{
		switch (event.GetEventType())
		{
		case EventType::WindowClosed:
			b_Open = false;
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