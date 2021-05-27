#include "ltpch.h"
#include "LayerStack.h"

#include "Layer.h"

#include "Events/Event.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/WindowEvents.h"

namespace Light {

	LayerStack* LayerStack::s_Context = nullptr;

	LayerStack::LayerStack()
	{
		s_Context = this; // TODO: ASSERT
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::OnUpdate(float deltaTime)
	{
		for (auto it = m_Begin; it != m_End; it++)
			(*it)->OnUpdate(deltaTime);
	}

	void LayerStack::OnUserInterfaceUpdate()
	{
		for (auto it = m_Begin; it != m_End; it++)
			(*it)->OnUserInterfaceUpdate();
	}

	void LayerStack::OnEvent(const Event& event)
	{
		switch (event.GetEventType())
		{
		// Mouse
		case EventType::MouseMoved:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnButtonPressed((ButtonPressedEvent&)event)) return;

		case EventType::ButtonPressed:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnButtonPressed((ButtonPressedEvent&)event)) return;
			return;
		case EventType::ButtonReleased:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnButtonReleased((ButtonReleasedEvent&)event)) return;
			return;
		case EventType::WheelScrolled:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnWheelScrolled((WheelScrolledEvent&)event)) return;
			return;

		// Keyboard
		case EventType::KeyPressed:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnKeyPressed((KeyPressedEvent&)event)) return;
			return;
		case EventType::KeyReleased:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnKeyReleased((KeyReleasedEvent&)event)) return;
			return;

		// Window
		case EventType::WindowClosed:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnWindowClosed((WindowClosedEvent&)event)) return;
			return;
		case EventType::WindowResized:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnWindowResized((WindowResizedEvent&)event)) return;
			return;
		case EventType::WindowMoved:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnWindowMoved((WindowMovedEvent&)event)) return;
			return;
		case EventType::WindowLostFocus:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnWindowLostFocus((WindowLostFocusEvent&)event)) return;
			return;
		case EventType::WindowGainFocus:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnWindowGainFocus((WindowGainFocusEvent&)event)) return;
			return;
		}
	}

	void LayerStack::AttachLayerImpl(Layer* layer)
	{
		m_Layers.push_back(layer);
		m_Begin = m_Layers.begin();
		m_End = m_Layers.end();

		LT_ENGINE_TRACE("LayerStack::PushLayer: Attached [{}]", layer->GetName());
	}

	void LayerStack::DetatchLayerImpl(Layer* layer)
	{
		m_Layers.erase(std::find(m_Layers.begin(), m_Layers.end(), layer));
		m_Begin = m_Layers.begin();
		m_End = m_Layers.end();

		LT_ENGINE_TRACE("LayerStack::PushLayer: Detatched[{}]", layer->GetName());
	}

}