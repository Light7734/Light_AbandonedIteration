#include "ltpch.h"
#include "dxBlender.h"

#include "dxSharedContext.h"

namespace Light {

	dxBlender::dxBlender(std::shared_ptr<dxSharedContext> sharedContext)
		: m_Context(sharedContext)
	{
		// factor map
		m_FactorMap = {
			// constants
			{ BlendFactor::ZERO, D3D11_BLEND_ZERO },
			{ BlendFactor::ONE, D3D11_BLEND_ONE },

			// source
			{ BlendFactor::SRC_COLOR, D3D11_BLEND_SRC_COLOR },
			{ BlendFactor::INVERSE_SRC_COLOR, D3D11_BLEND_INV_SRC_COLOR },

			{ BlendFactor::SRC_ALPHA, D3D11_BLEND_SRC_ALPHA },
			{ BlendFactor::INVERSE_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA },

			// destination
			{ BlendFactor::DST_COLOR, D3D11_BLEND_DEST_COLOR },
			{ BlendFactor::INVERSE_DST_COLOR, D3D11_BLEND_INV_DEST_COLOR },

			{ BlendFactor::DST_ALPHA, D3D11_BLEND_DEST_ALPHA },
			{ BlendFactor::INVERSE_DST_ALPHA, D3D11_BLEND_INV_DEST_ALPHA },

			// source1
			{ BlendFactor::SRC1_COLOR, D3D11_BLEND_SRC1_COLOR },
			{ BlendFactor::INVERSE_SRC1_COLOR, D3D11_BLEND_INV_SRC1_COLOR },

			{ BlendFactor::SRC1_ALPHA, D3D11_BLEND_SRC1_ALPHA },
			{ BlendFactor::INVERSE_SRC1_ALPHA, D3D11_BLEND_INV_SRC1_ALPHA }
		};

		// blender desc
		m_Desc = { };
		
		m_Desc.RenderTarget[0].BlendEnable = true;
		m_Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
		m_Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		m_Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		m_Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		m_Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		m_Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		m_Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		// create blend state
		HRESULT hr; 
		DXC(m_Context->GetDevice()->CreateBlendState( &m_Desc, &m_BlendState ) );
	}

	void dxBlender::Enable(BlendFactor srcFactor, BlendFactor dstFactor)
	{
		// update desc
		m_Desc.RenderTarget[0].BlendEnable = true;
		m_Desc.RenderTarget[0].SrcBlend = m_FactorMap[srcFactor];
		m_Desc.RenderTarget[0].DestBlend = m_FactorMap[dstFactor];

		// re-create blind state
		HRESULT hr;
		DXC(m_Context->GetDevice()->CreateBlendState(&m_Desc, &m_BlendState));

		// bind blend state
		m_Context->GetDeviceContext()->OMSetBlendState(m_BlendState.Get(), nullptr, 0xffffffff);
	}

	void dxBlender::Disable()
	{
		// update desc
		m_Desc.RenderTarget[0].BlendEnable = false;

		// re-create blind state
		HRESULT hr;
		DXC(m_Context->GetDevice()->CreateBlendState(&m_Desc, &m_BlendState));

		// bind blend state
		m_Context->GetDeviceContext()->OMSetBlendState(m_BlendState.Get(), nullptr, 0xffffffff);
	}

}