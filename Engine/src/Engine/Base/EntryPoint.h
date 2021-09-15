#pragma once

#ifdef LIGHT_PLATFORM_WINDOWS

#include <LightEngine.h>

// to be defined in client project
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
	// failed engine assertion
	catch (Light::FailedEngineAssertion)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled 'FailedEngineAssertion'");
		exitCode = -1;
	}
	// failed client assertion
	catch (Light::FailedClientAssertion)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled 'FailedClientAssertion'");
		exitCode = -2;
	}
	// gl exception
	catch(Light::glException)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled 'glException'");
		exitCode = -3;
	}
	// dx exception
	catch (Light::dxException)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled 'dxException'");
		exitCode = -4;
	}
	catch (Light::vkException)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled 'dxException'");
		exitCode = -5;
	}

	delete application;
	return exitCode;
}

#elif defined(LIGHT_PLATFORM_LINUX)

#include <LightEngine.h>

// to be defined in client project
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
	// failed engine assertion
	catch (Light::FailedEngineAssertion)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled 'FailedEngineAssertion'");
		exitCode = -1;
	}
	// failed client assertion
	catch (Light::FailedClientAssertion)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled 'FailedClientAssertion'");
		exitCode = -2;
	}
	// gl exception
	catch (Light::glException)
	{
		LT_ENGINE_CRITICAL("main: exitting due to unhandled 'glException'");
		exitCode = -3;
	}

	delete application;
	return exitCode;
}

#endif