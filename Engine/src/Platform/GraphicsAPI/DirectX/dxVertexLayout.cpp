#include "ltpch.h"
#include "dxVertexLayout.h"
#include "dxSharedContext.h"

#include "dxShader.h"

namespace Light {

	dxVertexLayout::dxVertexLayout(std::shared_ptr<Shader> shader, const std::vector<std::pair<std::string, VertexElementType>>& elements, std::shared_ptr<dxSharedContext> sharedContext)
		: m_Context(sharedContext)
	{
		// occupy space for input elements
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementsDesc;
		inputElementsDesc.reserve(elements.size());

		// extract elements desc
		for (const auto& element : elements)
		{
			inputElementsDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{
			                               element.first.c_str(),
			                               0u,
			                               GetDxgiFormat(element.second),
			                               0u,
			                               D3D11_APPEND_ALIGNED_ELEMENT,
			                               D3D11_INPUT_PER_VERTEX_DATA,
										   0u });
		}

		std::shared_ptr<dxShader> dxpShader = std::dynamic_pointer_cast<dxShader>(shader);
		LT_ENGINE_ASSERT(dxpShader, "dxVertexLayout::dxVertexLayout: failed to cast 'Shader' to 'dxShader'");

		// create input layout (vertex layout)
		HRESULT hr;
		DXC(m_Context->GetDevice()->CreateInputLayout(&inputElementsDesc[0], inputElementsDesc.size(), dxpShader->GetVertexBlob().Get()->GetBufferPointer(), dxpShader->GetVertexBlob().Get()->GetBufferSize(), &m_InputLayout));
	}

	dxVertexLayout::~dxVertexLayout()
	{
		UnBind();
	}

	void dxVertexLayout::Bind()
	{
		m_Context->GetDeviceContext()->IASetInputLayout(m_InputLayout.Get());
	}

	void dxVertexLayout::UnBind()
	{
		m_Context->GetDeviceContext()->IASetInputLayout(nullptr);
	}

	DXGI_FORMAT dxVertexLayout::GetDxgiFormat(VertexElementType type)
	{
		switch (type)
		{
		// #todo: add char
		// int
		case Light::VertexElementType::Int1: return DXGI_FORMAT_R32_SINT;
		case Light::VertexElementType::Int2: return DXGI_FORMAT_R32G32_SINT;
		case Light::VertexElementType::Int3: return DXGI_FORMAT_R32G32B32_SINT;
		case Light::VertexElementType::Int4: return DXGI_FORMAT_R32G32B32A32_SINT;

		// uint
		case Light::VertexElementType::UInt1: return DXGI_FORMAT_R32_UINT;
		case Light::VertexElementType::UInt2: return DXGI_FORMAT_R32G32_UINT;
		case Light::VertexElementType::UInt3: return DXGI_FORMAT_R32G32B32_UINT;
		case Light::VertexElementType::UInt4: return DXGI_FORMAT_R32G32B32A32_UINT;

		// float
		case Light::VertexElementType::Float1: return DXGI_FORMAT_R32_FLOAT;
		case Light::VertexElementType::Float2: return DXGI_FORMAT_R32G32_FLOAT;
		case Light::VertexElementType::Float3: return DXGI_FORMAT_R32G32B32_FLOAT;
		case Light::VertexElementType::Float4: return DXGI_FORMAT_R32G32B32A32_FLOAT;

		// #todo:
		case Light::VertexElementType::Double1:
		case Light::VertexElementType::Double2:
		case Light::VertexElementType::Double3:
		case Light::VertexElementType::Double4:

		default: LT_ENGINE_ASSERT(false, "dxVertexLayout::GetDxgiFormat: invalid 'VertexElementType'");
		}
	}

}