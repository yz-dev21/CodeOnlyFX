#include "System/App.h"
#include "Core/Debug.h"
#include "System/Timer.h"

namespace co
{
	void App::Run()
	{
		m_ContextSettings = SetupContext();

		Debug::Active = m_ContextSettings.Debug;
		if (m_ContextSettings.Debug)
			Debug::Initialize();

		m_Window = std::make_unique<Window>(m_ContextSettings);

		Initialize();

		Timer timer{};
		while (m_Window->IsRunning())
		{
			timer.Tick();

			Update(timer.GetDeltaTime());
			Render(timer.GetDeltaTime());

			timer.Reset();

			m_Window->Update();
		}
		Cleanup();
	}
	ContextSettings App::SetupContext()
	{
		return ContextSettings();
	}
}