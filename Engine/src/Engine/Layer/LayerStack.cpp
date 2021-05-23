#include "LayerStack.h"

namespace Light {

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
		m_Begin = m_Layers.begin();
		m_End = m_Layers.end();

		LT_ENGINE_TRACE("LayerStack::PushLayer: Attached [{}]", layer->GetName());
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		m_Layers.erase(std::find(m_Layers.begin(), m_Layers.end(), layer));
		m_Begin = m_Layers.begin();
		m_End = m_Layers.end();

		LT_ENGINE_TRACE("LayerStack::PushLayer: Detatched[{}]", layer->GetName());
	}

	void LayerStack::OnEvent(Event& event)
	{
		switch (event.GetEventType())
		{
		case EventType::MouseMoved:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnMouseMoved((MouseMovedEvent&)event)) return;
			return;

		case EventType::ButtonPressed:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnButtonPressed((ButtonPressedEvent&)event)) return;
			return;
		case EventType::ButtonReleased:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnButtonReleased((ButtonReleasedEvent&)event)) return;
			return;

		case EventType::KeyPressed:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnKeyPressed((KeyPressedEvent&)event)) return;
			return;
		case EventType::KeyReleased:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnKeyReleased((KeyReleasedEvent&)event)) return;
			return;

		case EventType::WindowClosed:
			for (auto it = m_Begin; it != m_End; it++)
				if ((*it)->OnWindowClosed((WindowClosedEvent&)event)) return;
			return;
		}
	}

}