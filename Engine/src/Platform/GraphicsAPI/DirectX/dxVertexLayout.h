#pragma once

#include "Base.h"
#include "dxBase.h"
#include "Graphics/VertexLayout.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	class Shader;

	class dxVertexLayout : public VertexLayout
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;

		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;

	public:
		dxVertexLayout(Shader* shader, const std::vector<std::pair<std::string, VertexElementType>>& elements, void* sharedContext);
		~dxVertexLayout();

		void Bind() override;
		void UnBind() override;

	private:
		DXGI_FORMAT GetDxgiFormat(VertexElementType type);
	};

}