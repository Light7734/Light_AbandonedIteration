#pragma once

#include "Graphics/Blender.h"

#include "Base/Base.h"

namespace Light {

	class glBlender : public Blender
	{
	private:
		std::unordered_map<BlendFactor, unsigned int> m_FactorMap;

	public:
		glBlender();

		void Enable(BlendFactor srcFactor, BlendFactor dstFactor) override;
		void Disable() override;
	};

}