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
		float colors[] = { 1.2f, 0.4f, 0.9f, 1.0f }; // #todo: use a variable for this
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

}