#pragma once

#include "Base.h"

#include "Event.h"

#include <sstream>

namespace Light {

	class KeyPressedEvent : public Event
	{
	private:
		const int m_Key;

	public:
		KeyPressedEvent(int key): m_Key(key) {}

		inline int GetKey() const { return m_Key; }

		virtual std::string GetInfoLog() const override
		{
			std::stringstream ss;
			ss << "KeyPressed: " << m_Key;
		}
		EVENT_TYPE(KeyPressed)
	};

	class KeyReleasedEvent : public Event
	{
	private:
		const int m_Key;

	public:
		KeyReleasedEvent(int key): m_Key(key) {}

		inline int GetKey() const { return m_Key; }

		virtual std::string GetInfoLog() const override
		{
			std::stringstream ss;
			ss << "KeyReleased: " << m_Key;
		}
		EVENT_TYPE(KeyReleased)
	};


}