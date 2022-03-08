#pragma once

#include "Base/Base.hpp"
#include "UserInterface/UserInterface.hpp"

struct GLFWwindow;

namespace Light {

class glUserInterface: public UserInterface
{
private:
	GLFWwindow* m_WindowHandle;

public:
	glUserInterface() = default;
	~glUserInterface();

	void PlatformImplementation(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext) override;

	void Begin() override;
	void End() override;

	void LogDebugData() override;
};

} // namespace Light