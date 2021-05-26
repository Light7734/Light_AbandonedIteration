#include <LightEngine.h>

class TestLayer : public Light::Layer
{
public:
	TestLayer(const std::string& name) : Light::Layer(name) {}

	// Mouse events
	virtual bool OnMouseMoved(const Light::MouseMovedEvent& event) override { LT_ENGINE_TRACE("{}", event.GetInfoLog()); return false; }
	virtual bool OnButtonPressed(const Light::ButtonPressedEvent& event) override { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
	virtual bool OnButtonReleased(const Light::ButtonReleasedEvent& event) override { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
	virtual bool OnWheelScrolled(const Light::WheelScrolledEvent& event) override { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }

	// Keyboard events
	virtual bool OnKeyPressed(const Light::KeyPressedEvent& event) override 
	{ 
		LT_ENGINE_TRACE(event.GetInfoLog());
		return true; 
	}
	virtual bool OnKeyReleased(const Light::KeyReleasedEvent& event) override { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }

	// Window events
	virtual bool OnWindowClosed(const Light::WindowClosedEvent& event) override { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
	virtual bool OnWindowResized(const Light::WindowResizedEvent& event) { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
	virtual bool OnWindowMoved(const Light::WindowMovedEvent& event) { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
	virtual bool OnWindowLostFocus(const Light::WindowLostFocusEvent& event) { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
	virtual bool OnWindowGainFocus(const Light::WindowGainFocusEvent& event) { LT_ENGINE_TRACE(event.GetInfoLog()); return false; }
};
