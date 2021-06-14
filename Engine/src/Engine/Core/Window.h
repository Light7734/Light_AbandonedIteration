#pragma once

#include "Base.h"

namespace Light {

	class Event;
	class GraphicsContext;

	struct WindowProperties
	{
		std::string title;
		unsigned int width, height;
		bool vsync;
	};

	class Window
	{
	protected:
		std::unique_ptr<GraphicsContext> m_GraphicsContext;
		bool b_Open;

	public:
		static Window* Create(const WindowProperties& properties, std::function<void(Event&)> callback);

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		virtual ~Window() = default;

		virtual void SetProperties(const WindowProperties& properties) = 0;

		virtual void SetVisible(bool visible) = 0;

		inline GraphicsContext* GetGfxContext() { return m_GraphicsContext.get(); }

		inline bool IsOpen() const { return b_Open; }

		virtual void PollEvents() = 0;
		virtual void OnEvent(const Event& event) = 0;

		virtual unsigned int GetHeight() = 0;
		virtual unsigned int GetWidth()  = 0;

		virtual inline void* GetNativeHandle() = 0;

	protected:
		Window() = default;
	};

}