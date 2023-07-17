#include "Input/Keyboard.h"
#include "Core/Window.h"
#include <GLFW/glfw3.h>

using KeyState = std::pair<bool, bool>;
static std::map<int, KeyState> KeyMap;

namespace co
{
	void Keyboard::GLFWKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode)
	{
		if (action == GLFW_REPEAT)
		{
			KeyMap[key].first = true;
			KeyMap[key].second = true;
			return;
		}

		KeyMap[key].second = KeyMap[key].first;
		KeyMap[key].first = action != GLFW_RELEASE;
	}
	bool Keyboard::IsKeyHeld(Key key)
	{
		int code = static_cast<int>(key);

		auto it = KeyMap.find(code);
		if (it != KeyMap.end())
		{
			auto& state = KeyMap.at(code);
			return state.first && state.second;
		}
		else
			return false;
	}
	bool Keyboard::IsKeyPressed(Key key)
	{
		int code = static_cast<int>(key);

		auto it = KeyMap.find(code);
		if (it != KeyMap.end())
		{
			auto& state = KeyMap.at(code);
			return state.first && !state.second;
		}
		else
			return false;
	}
	bool Keyboard::IsKeyReleased(Key key)
	{
		int code = static_cast<int>(key);

		auto it = KeyMap.find(code);
		if (it != KeyMap.end())
		{
			auto& state = KeyMap.at(code);
			return !state.first && state.second;
		}
		else
			return false;
	}
}