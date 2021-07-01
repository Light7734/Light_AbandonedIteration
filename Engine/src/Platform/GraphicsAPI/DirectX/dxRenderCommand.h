#pragma once

#include "Base.h"
#include "Graphics/RenderCommand.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	class dxSharedContext;

	class dxRenderCommand : public RenderCommand
	{
	private:
		std::shared_ptr<dxSharedContext> m_Context;

	public:
		dxRenderCommand(std::shared_ptr<dxSharedContext> sharedContext);

		virtual void SwapBuffers() override;
		virtual void ClearBackBuffer() override;

		virtual void Draw(unsigned int count) override;
		virtual void DrawIndexed(unsigned int count) override;
	};

}