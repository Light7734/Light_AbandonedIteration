#pragma once

#include "Base.h"
#include "Core/Window.h"

struct GLFWwindow;

namespace Light {

	class Event;

	class wWindow : public Window
	{
	private:
		GLFWwindow* m_Handle = nullptr;
		WindowProperties m_Properties;

		std::function<void(Event&)> m_EventCallback;

	public:
		wWindow(const WindowProperties& properties, std::function<void(Event&)> callback);

		~wWindow();

		virtual void PollEvents() override;
		virtual void OnEvent(const Event& event) override;

		virtual unsigned int GetWidth() override;
		virtual unsigned int GetHeight() override;

		virtual inline void* GetNativeHandle() override { return m_Handle; }

	private:
		void BindGlfwEvents();
	};

}