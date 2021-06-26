#pragma once

#ifdef LIGHT_PLATFORM_WINDOWS

#include <LightEngine.h>

// To be defined in client project
extern Light::Application* Light::CreateApplication();

// #todo: use windows specific stuff
int main(int argc, char** argv)
{
	Light::Application* application = nullptr;
	int exitCode = 0;

	try
	{
		application = Light::CreateApplication();
		LT_ENGINE_ASSERT(application, "main: Light::Application is not intialized");

		application->GameLoop();
	}
	catch (Light::FailedAssertion)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled FailedAssertion");
		exitCode = -1;
	}
	catch(Light::glException)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled glException");
		exitCode = -2;
	}
	catch (Light::dxException)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled dxException");
		exitCode = -3;
	}

	delete application;
	return exitCode;
}

#elif defined(LIGHT_PLATFORM_LINUX)

#include <LightEngine.h>

// To be defined in client project
extern Light::Application* Light::CreateApplication();

// #todo: use linux specific stuff
int main(int argc, char* argv[])
{
	Light::Application* application = nullptr;
	int exitCode = 0;

	try
	{
		application = Light::CreateApplication();
		LT_ENGINE_ASSERT(application, "main: Light::Application is not intialized");

		application->GameLoop();
	}
	catch (Light::FailedAssertion)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled FailedAssertion");
		exitCode = -1;
	}
	catch(Light::glException)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled glException");
		exitCode = -2;
	}

	delete application;
	return exitCode;
}

#endif