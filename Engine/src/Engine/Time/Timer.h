#pragma once

#include "Base.h"

#include <chrono>

namespace Light {

	class Timer
	{
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_Start;

	public:
		Timer() : m_Start(std::chrono::steady_clock::now()) { }

		inline float GetElapsedTime() const { return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_Start).count()) / 1000.; }

		inline void Reset() { m_Start = std::chrono::steady_clock::now(); }
	};

	class DeltaTimer
	{
	private:
		Timer timer;

		float m_PreviousFrame = 0.0f;
		float m_DeltaTime = 60.0f / 1000.0f;
		
	public:
		void Update();

		inline float GetDeltaTime() const { return m_DeltaTime; }
	};

}