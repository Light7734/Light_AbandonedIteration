#pragma once

#include "Base/Base.hpp"
#include "Camera/SceneCamera.hpp"

#include <glm/glm.hpp>

namespace Light {

struct CameraComponent
{
	SceneCamera camera;
	bool isPrimary;

	CameraComponent()                       = default;
	CameraComponent(const CameraComponent&) = default;

	CameraComponent(SceneCamera _camera, bool _isPrimary = false)
	    : camera(_camera), isPrimary(_isPrimary)
	{
	}

	operator SceneCamera() { return camera; }
};

} // namespace Light