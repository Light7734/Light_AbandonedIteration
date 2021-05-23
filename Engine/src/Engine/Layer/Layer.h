#pragma once

#include "Base.h"

#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"

#include <string>

namespace Light {

	class Layer
	{
	private:
		std::string m_Name;
	public:
		Layer(const std::string& name): m_Name(name) {}
		virtual ~Layer() = default;

		inline const std::string& GetName() const { return m_Name; }

		// Mouse events
		virtual bool OnMouseMoved(const MouseMovedEvent& event) { return false; }
		virtual bool OnButtonPressed(const ButtonPressedEvent& event) { return false; }
		virtual bool OnButtonReleased(const ButtonReleasedEvent& event) { return false; }

		// Keyboard events
		virtual bool OnKeyPressed(const KeyPressedEvent& event) { return false; }
		virtual bool OnKeyReleased(const KeyReleasedEvent& event) { return false; }
	};

	class TestLayer : public Layer
	{
	public:
		TestLayer(const std::string& name): Layer(name) {}

		// Mouse events
		virtual bool OnMouseMoved(const MouseMovedEvent& event) { LT_ENGINE_TRACE("{}", event.GetInfoLog()); return false; }
		virtual bool OnButtonPressed(const ButtonPressedEvent& event) { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
		virtual bool OnButtonReleased(const ButtonReleasedEvent& event) { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }

		// Keyboard events
		virtual bool OnKeyPressed(const KeyPressedEvent& event) { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
		virtual bool OnKeyReleased(const KeyReleasedEvent& event) { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
	};

}