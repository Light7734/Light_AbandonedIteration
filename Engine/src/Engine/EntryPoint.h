#pragma once

#ifdef LIGHT_PLATFORM_WINDOWS

// To be defined in client project
extern Light::Application* Light::CreateApplication();

int main(int argc, char** argv)
{
	auto application = Light::CreateApplication();
	application->GameLoop();
	delete application;
}

#endif