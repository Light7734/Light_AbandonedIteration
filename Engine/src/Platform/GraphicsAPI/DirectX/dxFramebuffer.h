#pragma once

#include "Base.h"
#include "Graphics/Framebuffer.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {
	
	class dxSharedContext;

	class dxFramebuffer : public Framebuffer
	{
	private:
		std::shared_ptr<dxSharedContext> m_Context;
		
		FramebufferSpecification m_Specification;

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_ColorAttachment;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_DepthStencilAttachment;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ResourceView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView;

	public:
		dxFramebuffer(const FramebufferSpecification& specification, std::shared_ptr<dxSharedContext> sharedContext);

		inline void* GetColorAttachment() override { return (void*)m_ResourceView.Get(); }

		void BindAsTarget() override;
		void BindAsResource() override;

	};

}