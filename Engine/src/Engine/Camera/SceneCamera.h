#pragma once

#include "Camera.h"

#include "Base/Base.h"

namespace Light {

	class SceneCamera : public Camera
	{
	private:
		float m_OrthoSize;
		float m_OrthoNearPlane, m_OrthoFarPlane;

		float m_AspectRatio;

	public:
		SceneCamera();

		void SetViewportSize(unsigned int width, unsigned int height);

	private:
		void CalculateProjection();
	};

}