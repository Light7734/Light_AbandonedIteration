#include "ltpch.h"
#include "Timer.h"

namespace Light {

	void DeltaTimer::Update()
	{
		auto current = std::chrono::steady_clock::now();
		m_DeltaTime = ((std::chrono::duration_cast<std::chrono::milliseconds>(current - m_Previous)).count()) / 1000.0f;
		m_Previous = current;
	}

}