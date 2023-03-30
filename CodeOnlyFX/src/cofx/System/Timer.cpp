#include "System/Timer.h"
#include "Core/Debug.h"

namespace co
{
	Timer::Timer()
	{
		Reset();

		m_TimeScale = 1.f;
	}
	void Timer::Reset()
	{
		m_StartTime = std::chrono::steady_clock::now();
	}
	float Timer::GetDeltaTime() const
	{
		return m_DeltaTime.count();
	}
	float Timer::GetTimeScale() const
	{
		return m_TimeScale;
	}
	void Timer::SetTimeScale(float t)
	{
		m_TimeScale = t;
	}
	void Timer::Tick()
	{
		m_DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_StartTime.time_since_epoch());
	}
}