#pragma once

#include "Base.h"

#include <glm/glm.hpp>

namespace Light {

	class Camera
	{
	private:
		glm::vec2 m_Position;
		float m_AspectRatio;
		float m_ZoomLevel;

		const glm::vec3 m_Up;

		glm::mat4 m_Projection;
		glm::mat4 m_View;

	public:	
		Camera(const glm::vec2& position, float aspectRatio, float zoomLevel);

		// CAMERA //
		void CalculateView();
		void CalculateProjection();

		inline const glm::mat4& GetView() const { return m_View; }
		inline const glm::mat4& GetProjection() const { return m_Projection; }

		// CAMERA_CONTROLLER //
		void Move(const glm::vec2& position);
	};

}