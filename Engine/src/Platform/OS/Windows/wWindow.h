#pragma once

#include "Base.h"
#include "Core/Window.h"

struct GLFWwindow;

namespace Light {

	class Event;

	class wWindow : public Window
	{
	private:
		// #todo: don't handle Windows's window with glfw, create it yourself
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

		void SetSize(const glm::uvec2& size, bool add = false) override;

		void SetVSync(bool vsync, bool toggle = false) override;
		void SetVisibility(bool visible, bool toggle = false) override;

	private:
		void BindGlfwEvents();
	};

}