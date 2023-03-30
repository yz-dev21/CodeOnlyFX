#pragma once

#include <chrono>

namespace co
{
	class Timer
	{
	private:
		std::chrono::high_resolution_clock::time_point m_StartTime;
		std::chrono::milliseconds m_DeltaTime;
		float m_TimeScale;
	public:
		Timer();

		void Reset();

		float GetDeltaTime() const;

		float GetTimeScale() const;
		void SetTimeScale(float t = 1.f);

		void Tick();
	};
}