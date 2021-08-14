#pragma once

// #todo: make proper math stuff

// this is a temporary header file to extend the glm math
// light engine will either have it's own math library or extend upon the glm

#include <glm/glm.hpp>

namespace Light {

	class Math
	{
	public:
		static float Rand(int min, int max, int decimals = 0);
		static glm::vec2 RandVec2(int min, int max, int decimals = 0);
		static glm::vec3 RandVec3(int min, int max, int decimals = 0);
	};

}
