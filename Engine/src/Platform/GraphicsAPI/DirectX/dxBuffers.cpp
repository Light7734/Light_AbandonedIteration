#include "ltpch.h"
#include "dxBuffers.h"

#include "dxSharedContext.h"

namespace Light {

	dxVertexBuffer::dxVertexBuffer(unsigned int count, unsigned int stride, float* vertices, void* sharedContext)
		: m_Stride(stride)
	{
		HRESULT hr;

		dxSharedContext* dxContext = static_cast<dxSharedContext*>(sharedContext);
		LT_ENGINE_ASSERT(dxContext, "dxShader::dxShader: invalid dxContext");

		m_Device = dxContext->device;
		m_DeviceContext = dxContext->deviceContext;

		D3D11_BUFFER_DESC desc = { 0 };
		D3D11_SUBRESOURCE_DATA sd = { 0 };


		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		desc.ByteWidth = count * stride;
		desc.StructureByteStride = stride;

		sd.pSysMem = vertices;

		DXC(m_Device->CreateBuffer(&desc, &sd, &m_Buffer));
	}

	dxVertexBuffer::~dxVertexBuffer()
	{
	}

	void dxVertexBuffer::Bind()
	{
		static const unsigned int offset = 0u;
		m_DeviceContext->IASetVertexBuffers(0u, 1u, m_Buffer.GetAddressOf(), &m_Stride, &offset);
	}

	void dxVertexBuffer::UnBind()
	{
	}

}