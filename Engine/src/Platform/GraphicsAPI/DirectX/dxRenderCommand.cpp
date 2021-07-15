#include "ltpch.h"
#include "dxRenderCommand.h"
#include "dxSharedContext.h"

namespace Light {

	dxRenderCommand::dxRenderCommand(std::shared_ptr<dxSharedContext> sharedContext)
		: m_Context(sharedContext)
	{ }

	void dxRenderCommand::SwapBuffers()
	{
#ifdef LIGHT_DEBUG
		HRESULT hr;
		if (FAILED(hr = m_Context->GetSwapChain()->Present(0u, 0u)))
		{
			if (hr == DXGI_ERROR_DEVICE_REMOVED)
			{
				LT_ENGINE_CRITICAL("dxRenderCommand::SwapBuffers: DeviceRemoved:");
				LT_ENGINE_CRITICAL("        {}", m_Context->GetDevice()->GetDeviceRemovedReason());
				throw dxException(hr, __FILE__, __LINE__);
			}
		}
#else
		m_Context->GetSwapChain()->Present(0u, 0u);
#endif
	}

	void dxRenderCommand::ClearBackBuffer()
	{
		float colors[] = { 0.1, 0.35f, 0.46f, 1.0f }; // #todo: use a local variable for this
		m_Context->GetDeviceContext()->ClearRenderTargetView(m_Context->GetRenderTargetView().Get(), colors);
	}

	void dxRenderCommand::Draw(unsigned int count)
	{
		m_Context->GetDeviceContext()->Draw(count, 0u);
	}

	void dxRenderCommand::DrawIndexed(unsigned int count)
	{
		m_Context->GetDeviceContext()->DrawIndexed(count, 0u, 0u);
	}

	void dxRenderCommand::DefaultTargetFramebuffer()
	{
		m_Context->GetDeviceContext()->OMSetRenderTargets(1, m_Context->GetRenderTargetView().GetAddressOf(), nullptr);
	}

	void dxRenderCommand::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		// create viewport
		D3D11_VIEWPORT viewport;

		viewport.TopLeftX = x;
		viewport.TopLeftY = y;

		viewport.Width = width;
		viewport.Height = height;

		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		// set viewport
		m_Context->GetDeviceContext()->RSSetViewports(1u, &viewport);
	}

}