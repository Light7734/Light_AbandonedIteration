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

		std::function<void(Event&)> m_EventCallback;

	public:
		wWindow(std::function<void(Event&)> callback);

		~wWindow();

		void PollEvents() override;
		void OnEvent(const Event& event) override;

		// Setters //
		void SetProperties(const WindowProperties& properties) override;

		void SetTitle(const std::string& title) override;

		void SetSize(const glm::uvec2& size) override;

		void SetVSync(bool vsync, bool toggle = false) override;
		void SetVisibility(bool visible, bool toggle = false) override;

	private:
		void BindGlfwEvents();
	};

}