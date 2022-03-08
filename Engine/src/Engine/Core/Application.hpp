#pragma once

#include "Base/Base.hpp"
#include "Debug/Instrumentor.hpp"
#include "Input/Input.hpp"
#include "Layer/LayerStack.hpp"
#include "Utility/ResourceManager.hpp"

namespace Light {

class Window;
class Event;

class Instrumentor;

class Application /* singleton */
{
private:
	static Application* s_Context;

private:
	Scope<Logger> m_Logger;
	Scope<Instrumentor> m_Instrumentor;
	Scope<LayerStack> m_LayerStack;
	Scope<Input> m_Input;
	Scope<ResourceManager> m_ResourceManager;

protected:
	Scope<Window> m_Window;

public:
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	virtual ~Application();

	void GameLoop();

	// To be defined in client project

	static void Quit();

protected:
	Application(std::string execName, std::vector<std::string> args);

private:
	void OnEvent(const Event& event);

	void LogDebugData();
};

extern Application* CreateApplication(std::string execName, std::vector<std::string> args);

} // namespace Light