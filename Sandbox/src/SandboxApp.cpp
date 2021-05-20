#include <LightEngine.h>

class Sandbox : public Light::Application
{
};

Light::Application* Light::CreateApplication()
{
	return new Sandbox();
}