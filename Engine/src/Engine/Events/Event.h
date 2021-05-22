#pragma once

#include "Base.h"

#include <ostream>

namespace Light {

	enum EventType
	{
		None = 0,

		// input
		MouseMoved, ButtonPressed, ButtonReleased, // mouse
		KeyPressed, KeyReleased, // keyboard

		// window
		WindowMoved, WindowResized, WindowClosed,
	};

#define EVENT_TYPE(x) virtual EventType GetType() override { return x; }

	class Event
	{
	private:
		bool b_Handled;

	public:
		virtual EventType GetType() = 0;
		virtual std::string GetInfoLog() const = 0;

		inline bool IsHandled() const { return b_Handled; }

		friend std::ostream & operator<<(std::ostream & os, const Event& e)
		{
			return os << e.GetInfoLog();
		}
	};

}