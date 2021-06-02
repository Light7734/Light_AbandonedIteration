#pragma once

#include "Base.h"
#include "dxBase.h"
#include "Graphics/GraphicsContext.h"

#include <d3d11.h>
#include <wrl.h>

struct GLFWwindow;

namespace Light {

	class dxGraphicsContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;

		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

	public:
		dxGraphicsContext(GLFWwindow* windowHandle);

		virtual void OnWindowResize(const WindowResizedEvent& event) override;

		virtual void LogDebugData() override;
	};

}