#pragma once

#include "Base/Base.hpp"
#include "Graphics/GraphicsContext.hpp"

struct GLFWwindow;

namespace Light {

class glGraphicsContext: public GraphicsContext
{
private:
	GLFWwindow* m_WindowHandle;

public:
	glGraphicsContext(GLFWwindow* windowHandle);

	void LogDebugData() override;

private:
	void SetDebugMessageCallback();
};

} // namespace Light