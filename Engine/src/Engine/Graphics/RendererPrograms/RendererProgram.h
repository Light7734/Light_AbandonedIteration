#pragma once

#include "Base.h"

namespace Light {

	class RendererProgram
	{
		virtual void Map() = 0;
		virtual void Bind() = 0;
	};

}