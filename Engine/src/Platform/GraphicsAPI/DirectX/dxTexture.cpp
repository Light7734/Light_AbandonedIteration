#include "ltpch.h"
#include "dxTexture.h"

#include "dxSharedContext.h"

namespace Light {

	dxTexture::dxTexture(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels, std::shared_ptr<dxSharedContext> sharedContext)
		: m_Context(sharedContext)
	{
		D3D11_TEXTURE2D_DESC textureDesc = { 0 };
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 0;
		textureDesc.ArraySize = 1;
		textureDesc.Format =  components == 4 ? DXGI_FORMAT_R8G8B8A8_UNORM : 
		                      components == 3 ? DXGI_FORMAT_R8G8B8A8_UNORM : 
		                      components == 2 ? DXGI_FORMAT_R8G8B8A8_UNORM : 
		                      components == 1 ? DXGI_FORMAT_R8G8B8A8_UNORM : DXGI_FORMAT_UNKNOWN;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		textureDesc.CPUAccessFlags = NULL;
		textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

		HRESULT hr;
		DXC(m_Context->device->CreateTexture2D(&textureDesc, nullptr, &m_Texture));
		m_Context->deviceContext->UpdateSubresource(m_Texture.Get(), 0u, nullptr, pixels, width * 4, 0u);

		m_Texture->GetDesc(&textureDesc);

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = { };
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0u;
		shaderResourceViewDesc.Texture2D.MipLevels = -1;

		m_Context->device->CreateShaderResourceView(m_Texture.Get(), &shaderResourceViewDesc, &m_ResourceView);
		m_Context->deviceContext->GenerateMips(m_ResourceView.Get());

		D3D11_SAMPLER_DESC samplerDesc = { };
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MinLOD = 0.0f;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		m_Context->device->CreateSamplerState(&samplerDesc, &m_SamplerState);
	}

	void dxTexture::Bind(unsigned int slot /* = 0 */)
	{
		m_Context->deviceContext->PSSetSamplers(slot, 1u, m_SamplerState.GetAddressOf());
		m_Context->deviceContext->PSSetShaderResources(slot, 1u, m_ResourceView.GetAddressOf());
	}

}