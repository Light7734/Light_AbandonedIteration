#include "ltpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Light {

	SceneCamera::SceneCamera()
		: m_OrthoSize(1000.0f),
		  m_OrthoNearPlane(-1.0f),
		  m_OrthoFarPlane(1.0f),
		  m_AspectRatio(16.0f / 9.0f)
	{
		CalculateProjection();
	}

	void SceneCamera::SetViewportSize(unsigned int width, unsigned int height)
	{
		m_AspectRatio = width / (float)height;
		CalculateProjection();
	}

	void SceneCamera::CalculateProjection()
	{
		m_Projection = glm::ortho(-m_OrthoSize * 0.5f * m_AspectRatio,
		                           m_OrthoSize * 0.5f * m_AspectRatio,
		                          -m_OrthoSize * 0.5f,
		                           m_OrthoSize * 0.5f,
		                           m_OrthoFarPlane,
		                           m_OrthoNearPlane);
	}

}