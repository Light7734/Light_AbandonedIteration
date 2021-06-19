#include "ltpch.h"
#include "dxRenderCommand.h"

#include "dxSharedContext.h"

namespace Light {

	dxRenderCommand::dxRenderCommand(std::shared_ptr<dxSharedContext> sharedContext)
		: m_Context(sharedContext)
	{
	}

	dxRenderCommand::~dxRenderCommand()
	{
	}

	void dxRenderCommand::SwapBuffers()
	{
		m_Context->swapChain->Present(0, 0);
	}

	void dxRenderCommand::ClearBackBuffer()
	{
		float colors[] = { 1.2f, 0.4f, 0.9f, 1.0f };
		m_Context->deviceContext->ClearRenderTargetView(m_Context->renderTargetView.Get(), colors);
	}

	void dxRenderCommand::Draw(unsigned int count)
	{
		m_Context->deviceContext->Draw(count, 0u);
	}

	void dxRenderCommand::DrawIndexed(unsigned int count)
	{
		m_Context->deviceContext->DrawIndexed(count, 0u, 0u);
	}

}