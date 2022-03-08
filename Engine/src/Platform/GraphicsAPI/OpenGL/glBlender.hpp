#pragma once

#include "Base/Base.hpp"
#include "Graphics/Blender.hpp"

namespace Light {

class glBlender: public Blender
{
private:
	std::unordered_map<BlendFactor, unsigned int> m_FactorMap;

public:
	glBlender();

	void Enable(BlendFactor srcFactor, BlendFactor dstFactor) override;
	void Disable() override;
};

} // namespace Light