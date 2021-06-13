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

		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		desc.ByteWidth = count * stride;
		desc.StructureByteStride = stride;

		DXC(m_Device->CreateBuffer(&desc, nullptr, &m_Buffer));
	}

	dxVertexBuffer::~dxVertexBuffer()
	{
	}

	void* dxVertexBuffer::Map()
	{
		m_DeviceContext->Map(m_Buffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_Map);
		return m_Map.pData;
	}

	void dxVertexBuffer::UnMap()
	{
		m_DeviceContext->Unmap(m_Buffer.Get(), NULL);
	}

	void dxVertexBuffer::Bind()
	{
		static const unsigned int offset = 0u;
		m_DeviceContext->IASetVertexBuffers(0u, 1u, m_Buffer.GetAddressOf(), &m_Stride, &offset);
	}

	void dxVertexBuffer::UnBind()
	{
	}


	dxIndexBuffer::dxIndexBuffer(unsigned int count, unsigned int* indices, void* sharedContext)
	{
		HRESULT hr;

		dxSharedContext* dxContext = static_cast<dxSharedContext*>(sharedContext);
		LT_ENGINE_ASSERT(dxContext, "dxShader::dxShader: invalid dxContext");

		m_Device = dxContext->device;
		m_DeviceContext = dxContext->deviceContext;

		D3D11_BUFFER_DESC bufferDesc = { 0 };
		D3D11_SUBRESOURCE_DATA sd = { 0 };
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;

		bufferDesc.ByteWidth = count * sizeof(unsigned int);
		bufferDesc.StructureByteStride = sizeof(unsigned int);

		sd.pSysMem = indices;

		DXC(m_Device->CreateBuffer(&bufferDesc, &sd, &m_Buffer));
	}

	dxIndexBuffer::~dxIndexBuffer()
	{
	}

	void dxIndexBuffer::Bind()
	{
		m_DeviceContext->IASetIndexBuffer(m_Buffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
	}

	void dxIndexBuffer::UnBind()
	{
	}

}