#pragma once

#include "Base.h"

#include "Core/Window.h"

#include <GLFW/glfw3.h>

#include <memory>

namespace Light {

	class wWindow : public Window
	{
	private:
		GLFWwindow* m_Handle = nullptr;
		WindowProperties m_Properties;
	public:
		wWindow(const WindowProperties& properties);

		~wWindow();

		virtual void OnUpdate() override;

		virtual unsigned int GetWidth() override;
		virtual unsigned int GetHeight() override;

		virtual inline void* GetNativeHandle() override { return m_Handle; }
	};

}