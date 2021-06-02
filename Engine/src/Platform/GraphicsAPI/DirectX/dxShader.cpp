#include "ltpch.h"
#include "dxShader.h"

#include "dxSharedContext.h"

#include <d3dcompiler.h>

namespace Light {


	dxShader::dxShader(const std::string& vertexSource, const std::string& pixelSource, void* sharedContext)
	{
		HRESULT hr;

		dxSharedContext* dxContext = static_cast<dxSharedContext*>(sharedContext);
		LT_ENGINE_ASSERT(dxContext, "dxShader::dxShader: invalid dxContext");

		m_Device = dxContext->device;
		m_DeviceContext = dxContext->deviceContext;

		Microsoft::WRL::ComPtr<ID3DBlob> ps = nullptr, vsErr = nullptr, psErr = nullptr;

		DXC(D3DCompile(vertexSource.c_str(), vertexSource.length(), NULL, nullptr, nullptr, "main", "vs_4_0", NULL, NULL, &m_VertexBlob, &vsErr));
		DXC(D3DCompile(pixelSource.c_str(), pixelSource.length(), NULL, nullptr, nullptr, "main", "ps_4_0", NULL, NULL, &ps, &psErr));

		LT_ENGINE_ASSERT(!vsErr.Get(), "dxShader::dxShader: vertex shader compile error: {}", (char*)vsErr->GetBufferPointer());
		LT_ENGINE_ASSERT(!psErr.Get(), "dxShader::dxShader: vertex shader compile error: {}", (char*)psErr->GetBufferPointer());

		DXC(m_Device->CreateVertexShader(m_VertexBlob->GetBufferPointer(), m_VertexBlob->GetBufferSize(), NULL, &m_VertexShader));
		DXC(m_Device->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), NULL, &m_PixelShader));
	}

	dxShader::~dxShader()
	{
	}

	void dxShader::Bind()
	{
		m_DeviceContext->VSSetShader(m_VertexShader.Get(), nullptr, 0u);
		m_DeviceContext->PSSetShader(m_PixelShader.Get(), nullptr, 0u);
	}

	void dxShader::UnBind()
	{
	}

}