#pragma once

#include "Base.h"
#include "Graphics/RenderCommand.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	class dxRenderCommand : public RenderCommand
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

	public:
		dxRenderCommand(void* sharedContext);
		~dxRenderCommand();

		virtual void SwapBuffers() override;
		virtual void ClearBackBuffer() override;

		virtual void Draw(unsigned int count) override;
		virtual void DrawIndexed(unsigned int count) override;

	};

}