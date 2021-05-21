#include "wWindow.h"

namespace Light {

	Window* Window::Create(const WindowProperties& properties)
	{
		return new wWindow(properties);
	}

	wWindow::wWindow(const WindowProperties& properties)
		: m_Properties(properties)
	{
		if (!glfwInit()) __debugbreak();

		m_Handle = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_Handle);
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

}