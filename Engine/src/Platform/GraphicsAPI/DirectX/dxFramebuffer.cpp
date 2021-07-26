#include "ltpch.h"
#include "dxFramebuffer.h"
#include "dxSharedContext.h"

namespace Light {

	dxFramebuffer::dxFramebuffer(const FramebufferSpecification& specification, Ref<dxSharedContext> sharedContext)
		: m_Specification(specification), m_Context(sharedContext)
	{
		HRESULT hr;
		D3D11_TEXTURE2D_DESC textureDesc = { };
		textureDesc.Width = specification.width;
		textureDesc.Height = specification.height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1u;
		textureDesc.SampleDesc.Quality = 0u;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = NULL;
		textureDesc.MiscFlags = NULL;
		DXC(m_Context->GetDevice()->CreateTexture2D(&textureDesc, nullptr, &m_ColorAttachment));

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = { };
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		DXC(m_Context->GetDevice()->CreateShaderResourceView(m_ColorAttachment.Get(), &shaderResourceViewDesc, &m_ResourceView));

		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = textureDesc.Format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0u;
		DXC(m_Context->GetDevice()->CreateRenderTargetView(m_ColorAttachment.Get(), &rtvDesc, &m_RenderTargetView));
	}

	void dxFramebuffer::BindAsTarget()
	{
		FLOAT color[] = {
			m_Specification.defaultColor.r,
			m_Specification.defaultColor.g,
			m_Specification.defaultColor.b,
			m_Specification.defaultColor.a,
		};

		m_Context->GetDeviceContext()->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), nullptr);
		m_Context->GetDeviceContext()->ClearRenderTargetView(m_RenderTargetView.Get(), color);

		D3D11_VIEWPORT viewport;

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;

		viewport.Width = m_Specification.width;
		viewport.Height = m_Specification.height;

		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		// set viewport
		m_Context->GetDeviceContext()->RSSetViewports(1u, &viewport);
	}

	void dxFramebuffer::BindAsResource()
	{
		LT_ENGINE_ERROR("dxFramebuffer::BindAsResource: NO_IMPLEMENT");
	}

	void dxFramebuffer::Resize(const glm::vec2& size)
	{
		m_Specification.width = std::clamp(size.x, 1.0f, 16384.0f);  
		m_Specification.height= std::clamp(size.y, 1.0f, 16384.0f);  

		D3D11_TEXTURE2D_DESC textureDesc;
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;	

		m_ColorAttachment->GetDesc(&textureDesc);
		m_RenderTargetView->GetDesc(&rtvDesc);
		m_ResourceView->GetDesc(&srvDesc);

		textureDesc.Width = m_Specification.width;
		textureDesc.Height = m_Specification.height;

		HRESULT hr;
		DXC(m_Context->GetDevice()->CreateTexture2D(&textureDesc, nullptr, &m_ColorAttachment));
		DXC(m_Context->GetDevice()->CreateRenderTargetView(m_ColorAttachment.Get(), &rtvDesc, &m_RenderTargetView));
		DXC(m_Context->GetDevice()->CreateShaderResourceView(m_ColorAttachment.Get(), &srvDesc, &m_ResourceView));
	}

}	