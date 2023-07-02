#include "System/Timer.h"
#include "Core/Debug.h"

namespace co
{
	Timer::Timer()
	{
		Reset();
	}
	const std::chrono::steady_clock::time_point& Timer::Now() const
	{
		return m_Now;
	}
	const std::chrono::steady_clock::time_point& Timer::Last() const
	{
		return m_Last;
	}
	void Timer::Reset()
	{
		m_Now = std::chrono::steady_clock::now();
		m_Last = {};
	}
	void Timer::Tick()
	{
		m_Last = m_Now;
		m_Now = std::chrono::steady_clock::now();
	}
	float Timer::GetElapsed() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_Now - m_Last).count();
	}
}