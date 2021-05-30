#include "ltpch.h"
#include "Application.h"

#include "Logger.h"
#include "Window.h"

#include "Events/Event.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"

#include "UserInterface/UserInterface.h"

namespace Light {

	Application::Application()
	{
		Logger::Initialize();
		m_Window = std::unique_ptr<Window>(Window::Create({ "Title", 800u, 600u, false }, std::bind(&Application::OnEvent, this , std::placeholders::_1)));
	}

	Application::~Application()
	{
		LT_ENGINE_INFO("Application::~Application: Terminating Application");
	}

	void Application::GameLoop()
	{
		LT_ENGINE_ASSERT(!m_LayerStack.IsEmpty(), "Application::GameLoop: Layerstack is empty");

		while (m_Window->IsOpen())
		{
			// Events
			m_Window->PollEvents();

			// Rendering
			m_Window->GetGfxContext()->GetRenderer()->Draw();

			// Buffer updates
			m_Window->GetGfxContext()->GetRenderCommand()->SwapBuffers();
			m_Window->GetGfxContext()->GetRenderCommand()->ClearBackBuffer();

			// Update
			// ...

			// UserInterface
			m_Window->GetGfxContext()->GetUserInterface()->Begin();
			m_Window->GetGfxContext()->GetUserInterface()->End();
		}
	}

	void Application::OnEvent(const Event& event)
	{
		// Window
		if (event.HasCategory(WindowEventCategory))
			m_Window->OnEvent(event);

		// UserInterface
		if (event.HasCategory(InputEventCategory))
			m_Window->GetGfxContext()->GetUserInterface()->OnInput(event);

		// Input
		// ...

		// Layers
		m_LayerStack.OnEvent(event);
	}

}