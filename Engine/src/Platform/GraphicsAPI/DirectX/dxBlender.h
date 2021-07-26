#pragma once

#include "Base.h"
#include "Graphics/Blender.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	class dxSharedContext;

	class dxBlender : public Blender
	{
	private:
		Ref<dxSharedContext> m_Context;
		std::unordered_map<BlendFactor, D3D11_BLEND> m_FactorMap;

		Microsoft::WRL::ComPtr<ID3D11BlendState> m_BlendState;

		D3D11_BLEND_DESC m_Desc;

	public:
		dxBlender(Ref<dxSharedContext> sharedContext);

		void Enable(BlendFactor srcFactor, BlendFactor dstFactor) override;
		void Disable() override;
	};

}