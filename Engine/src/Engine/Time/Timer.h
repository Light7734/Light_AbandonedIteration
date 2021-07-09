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
		std::chrono::time_point<std::chrono::steady_clock> m_Previous;

		float m_DeltaTime = 60.0f / 1000.0f;

	public:
		DeltaTimer(): m_Previous(std::chrono::steady_clock::now()) { }

		void Update();

		inline float GetDeltaTime() const { return m_DeltaTime; }
	};

}