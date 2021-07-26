#include "ltpch.h"
#include "dxTexture.h"
#include "dxSharedContext.h"

namespace Light {

	dxTexture::dxTexture(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels, Ref<dxSharedContext> sharedContext)
		: m_Context(sharedContext)
	{
		// texture desc
		D3D11_TEXTURE2D_DESC textureDesc = { };
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 0u;
		textureDesc.ArraySize = 1u;
		textureDesc.Format =  components == 4u ? DXGI_FORMAT_R8G8B8A8_UNORM : 
		                      components == 3u ? DXGI_FORMAT_R8G8B8A8_UNORM : 
		                      components == 2u ? DXGI_FORMAT_R8G8B8A8_UNORM : 
		                      components == 1u ? DXGI_FORMAT_R8G8B8A8_UNORM : DXGI_FORMAT_UNKNOWN;
		textureDesc.SampleDesc.Count = 1u;
		textureDesc.SampleDesc.Quality = 0u;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		textureDesc.CPUAccessFlags = NULL;
		textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

		// create texture
		HRESULT hr;
		DXC(m_Context->GetDevice()->CreateTexture2D(&textureDesc, nullptr, &m_Texture));
		m_Context->GetDeviceContext()->UpdateSubresource(m_Texture.Get(), 0u, nullptr, pixels, width * 4u, 0u);

		m_Texture->GetDesc(&textureDesc);

		// shader resource view desc
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = { };
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0u;
		shaderResourceViewDesc.Texture2D.MipLevels = -1;

		// create shader resource view
		m_Context->GetDevice()->CreateShaderResourceView(m_Texture.Get(), &shaderResourceViewDesc, &m_ResourceView);
		m_Context->GetDeviceContext()->GenerateMips(m_ResourceView.Get());

		// sampler desc
		D3D11_SAMPLER_DESC samplerDesc = { };
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MinLOD = 0.0f;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		// create sampler
		m_Context->GetDevice()->CreateSamplerState(&samplerDesc, &m_SamplerState);
	}

	void dxTexture::Bind(unsigned int slot /* = 0u */)
	{
		m_Context->GetDeviceContext()->PSSetSamplers(slot, 1u, m_SamplerState.GetAddressOf());
		m_Context->GetDeviceContext()->PSSetShaderResources(slot, 1u, m_ResourceView.GetAddressOf());
	}

}