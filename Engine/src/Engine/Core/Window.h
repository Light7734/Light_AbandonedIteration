#pragma once

#include "Base.h"

#include "Events/Event.h"

#include <string>

namespace Light {

	struct WindowProperties
	{
		std::string title;
		unsigned int width, height;
		bool vsync;
	};

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetHeight() = 0;
		virtual unsigned int GetWidth()  = 0;

		virtual inline void* GetNativeHandle() = 0;

		static Window* Create(const WindowProperties& properties, std::function<void(Event&)> callback);
	};

}