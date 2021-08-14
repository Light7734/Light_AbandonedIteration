#include "ltpch.h"
#include "TempExtensions.h"

#include <cmath>

namespace Light {

	float Math::Rand(int min, int max, int decimals /* = 0 */)
	{
		const int dec = std::pow(10, decimals);
		min *= dec;
		max *= dec;

		return (min + (rand() % (max)-min)) / (float)dec;
	}

	glm::vec2 Math::RandVec2(int min, int max, int decimals /* = 0 */)
	{
		const int dec = std::pow(10, decimals);
		min *= dec;
		max *= dec;

		float r1 = (min + (rand() % (max)-min)) / (float)dec;
		float r2 = (min + (rand() % (max)-min)) / (float)dec;

		return glm::vec2(r1, r2);
	}

	glm::vec3 Math::RandVec3(int min, int max, int decimals /* = 0 */)
	{
		const int dec = std::pow(10, decimals);
		min *= dec;
		max *= dec;

		float r1 = (min + (rand() % (max)-min)) / (float)dec;
		float r2 = (min + (rand() % (max)-min)) / (float)dec;
		float r3 = (min + (rand() % (max)-min)) / (float)dec;

		return glm::vec3(r1, r2, r3);
	}
}