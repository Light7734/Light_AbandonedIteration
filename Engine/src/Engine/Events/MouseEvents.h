#pragma once

#include "Base.h"

#include "Event.h"

#include <sstream>

namespace Light {

	class MouseMovedEvent : public Event
	{
	private:
		const float m_PositionX, m_PositionY;

	public:
		MouseMovedEvent(float x, float y) : m_PositionX(x), m_PositionY(y) {}

		inline float GetX() const { return m_PositionX; }
		inline float GetY() const { return m_PositionY; }

		virtual std::string GetInfoLog() const override
		{
			std::stringstream ss;
			ss << "MouseMoved: " << m_PositionX << ", " << m_PositionY;
			return ss.str();
		}
		EVENT_TYPE(MouseMoved)
	};

	class ButtonPressedEvent : public Event
	{
	private:
		const int m_Button;

	public:
		ButtonPressedEvent(int button): m_Button(button) {}

		inline int GetButton() const { return m_Button; }

		virtual std::string GetInfoLog() const override
		{
			std::stringstream ss;
			ss << "ButtonPressed: " << m_Button;
			return ss.str();
		}
		EVENT_TYPE(ButtonPressed)
	};

	class ButtonReleasedEvent : public Event
	{
	private:
		const int m_Button;

	public:
		ButtonReleasedEvent(int button) : m_Button(button) {}

		inline int GetButton() const { return m_Button; }

		virtual std::string GetInfoLog() const override
		{
			std::stringstream ss;
			ss << "ButtonReleased: " << m_Button;
			return ss.str();
		}
		EVENT_TYPE(ButtonReleased)
	};

}