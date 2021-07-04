#pragma once

#include "Base.h"

namespace Light {

	class Camera;

	class RendererProgram
	{
		virtual void SetCamera(const Camera& camera) = 0;

		virtual void Map() = 0;
		virtual void Bind() = 0;
	};

}