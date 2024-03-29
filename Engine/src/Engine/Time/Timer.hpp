#pragma once

#include "Base/Base.hpp"

#include <chrono>

namespace Light {

class Timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> m_Start;

public:
	Timer();

	inline float GetElapsedTime() const { return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_Start).count()) / 1000.; }

	inline void Reset() { m_Start = std::chrono::steady_clock::now(); }
};

class DeltaTimer
{
private:
	Timer timer;

	float m_PreviousFrame;
	float m_DeltaTime;

public:
	DeltaTimer();

	void Update();

	inline float GetDeltaTime() const { return m_DeltaTime; }
};

} // namespace Light