#include "ltpch.h"
#include "Timer.h"

namespace Light {

	void DeltaTimer::Update()
	{
		float currentFrame = timer.GetElapsedTime();
		m_DeltaTime = currentFrame - m_PreviousFrame;
		m_PreviousFrame = currentFrame;
	}

}