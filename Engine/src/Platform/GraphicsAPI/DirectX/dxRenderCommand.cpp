#include "ltpch.h"
#include "dxRenderCommand.h"

#include "dxSharedContext.h"

namespace Light {

	dxRenderCommand::dxRenderCommand(void* sharedContext)
	{
		dxSharedContext* dxContext = (dxSharedContext*)sharedContext;

		m_DeviceContext = dxContext->deviceContext;
		m_SwapChain = dxContext->swapChain;
		m_RenderTargetView = dxContext->renderTargetView;
	}

	dxRenderCommand::~dxRenderCommand()
	{
	}

	void dxRenderCommand::SwapBuffers()
	{
		m_SwapChain->Present(0, 0);
	}

	void dxRenderCommand::ClearBackBuffer()
	{
		float colors[] = { 1.2f, 0.4f, 0.9f, 1.0f };
		m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), colors);
	}

	void dxRenderCommand::Draw(unsigned int count)
	{
		m_DeviceContext->Draw(count, 0u);
	}

	void dxRenderCommand::DrawIndexed(unsigned int count)
	{

	}

}