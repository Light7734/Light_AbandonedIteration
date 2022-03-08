#pragma once

#include "Base/Base.hpp"
#include "Graphics/GraphicsContext.hpp"

#include <d3d11.h>
#include <wrl.h>

struct GLFWwindow;

namespace Light {

class dxGraphicsContext: public GraphicsContext
{
private:
	GLFWwindow* m_WindowHandle;

	Microsoft::WRL::ComPtr<ID3D11Debug> m_DebugInterface;

public:
	dxGraphicsContext(GLFWwindow* windowHandle);

	virtual void LogDebugData() override;

private:
	void SetupDeviceAndSwapChain(GLFWwindow* windowHandle);
	void SetupRenderTargets();
	void SetupDebugInterface();
};

} // namespace Light