#include "wWindow.h"

#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"

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

		glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS)
				callback(KeyPressedEvent(key));
			else
				callback(KeyReleasedEvent(key));
		});
	}

}