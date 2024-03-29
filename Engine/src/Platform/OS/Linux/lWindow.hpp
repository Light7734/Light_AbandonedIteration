#pragma once

#include "Base/Base.hpp"
#include "Core/Window.hpp"

struct GLFWwindow;

namespace Light {

class Event;
class WindowResizedEvent;

class lWindow: public Window
{
private:
	GLFWwindow* m_Handle;

	std::function<void(Event&)> m_EventCallback;

public:
	lWindow(std::function<void(Event&)> callback);
	~lWindow();

	/* events */
	void PollEvents() override;
	void OnEvent(const Event& event) override;

	//======================================== SETTERS ========================================//
	void SetProperties(const WindowProperties& properties, bool overrideVisibility = false) override;

	void SetTitle(const std::string& title) override;

	void SetSize(const glm::uvec2& size, bool additive = false) override;

	void SetVSync(bool vsync, bool toggle = false) override;
	void SetVisibility(bool visible, bool toggle = false) override;
	//======================================== SETTERS ========================================//

private:
	void OnWindowResize(const WindowResizedEvent& event);

	void BindGlfwEvents();
};

} // namespace Light