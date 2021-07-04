#include "ltpch.h"
#include "dxShader.h"
#include "dxSharedContext.h"

#include <d3dcompiler.h>

namespace Light {

	dxShader::dxShader(const std::string& vertexSource, const std::string& pixelSource, std::shared_ptr<dxSharedContext> sharedContext)
		: m_Context(sharedContext)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> ps = nullptr, vsErr = nullptr, psErr = nullptr;

		// compile shaders
		HRESULT hr;
		D3DCompile(vertexSource.c_str(), vertexSource.length(), NULL, nullptr, nullptr, "main", "vs_4_0", NULL, NULL, &m_VertexBlob, &vsErr);
		D3DCompile(pixelSource.c_str(), pixelSource.length(), NULL, nullptr, nullptr, "main", "ps_4_0", NULL, NULL, &ps, &psErr);

		// check
		LT_ENGINE_ASSERT(!vsErr.Get(), "dxShader::dxShader: vertex shader compile error: {}", (char*)vsErr->GetBufferPointer());
		LT_ENGINE_ASSERT(!psErr.Get(), "dxShader::dxShader: pixels shader compile error: {}", (char*)psErr->GetBufferPointer());

		// create shaders
		DXC(m_Context->GetDevice()->CreateVertexShader(m_VertexBlob->GetBufferPointer(), m_VertexBlob->GetBufferSize(), NULL, &m_VertexShader));
		DXC(m_Context->GetDevice()->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), NULL, &m_PixelShader));
	}

	dxShader::~dxShader()
	{
		UnBind();
	}

	void dxShader::Bind()
	{
		m_Context->GetDeviceContext()->VSSetShader(m_VertexShader.Get(), nullptr, 0u);
		m_Context->GetDeviceContext()->PSSetShader(m_PixelShader.Get(), nullptr, 0u);
	}

	void dxShader::UnBind()
	{
		m_Context->GetDeviceContext()->VSSetShader(nullptr, nullptr, 0u);
		m_Context->GetDeviceContext()->PSSetShader(nullptr, nullptr, 0u);
	}

	void dxShader::SetUniformMat4(const std::string& name, const glm::mat4& value)
	{
		LT_ENGINE_ERROR("dxShader::SetUniformMat4: NOT_IMPLEMENTED");
	}

}