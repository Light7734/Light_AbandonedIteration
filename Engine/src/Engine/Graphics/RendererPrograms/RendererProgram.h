#pragma once

#include "Base/Base.h"

namespace Light {

	class Camera;

	class RendererProgram
	{
		virtual void Map() = 0;
		virtual void UnMap() = 0;

		virtual void Bind() = 0;
	};

}