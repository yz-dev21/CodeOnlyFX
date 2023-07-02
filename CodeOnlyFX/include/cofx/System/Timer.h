#pragma once

#include <chrono>

namespace co
{
	class Timer
	{
	private:
		std::chrono::steady_clock::time_point m_Now, m_Last;
	public:
		Timer();

		const std::chrono::steady_clock::time_point& Now() const;
		const std::chrono::steady_clock::time_point& Last() const;
		void Reset();

		float GetElapsed() const;

		void Tick();
	};
}