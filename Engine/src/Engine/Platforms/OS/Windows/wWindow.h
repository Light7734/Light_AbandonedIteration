#pragma once

#include "Base.h"

#include "Core/Window.h"

#include "Events/Event.h"

#include <GLFW/glfw3.h>

#include <memory>

namespace Light {

	class wWindow : public Window
	{
	private:
		GLFWwindow* m_Handle = nullptr;
		WindowProperties m_Properties;

		std::function<void(Event&)> m_EventCallback;
	public:
		wWindow(const WindowProperties& properties, std::function<void(Event&)> callback);

		~wWindow();

		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;

		virtual unsigned int GetWidth() override;
		virtual unsigned int GetHeight() override;

		virtual inline void* GetNativeHandle() override { return m_Handle; }
	private:
		void BindGlfwEvents();
	};

}