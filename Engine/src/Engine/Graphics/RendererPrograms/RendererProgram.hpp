#pragma once

#include "Base/Base.hpp"

namespace Light {

class OrthographicCamera;

class RendererProgram
{
	virtual void Map()   = 0;
	virtual void UnMap() = 0;

	virtual void Bind() = 0;
};

} // namespace Light