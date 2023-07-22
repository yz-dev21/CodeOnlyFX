#include "Input/Keyboard.h"
#include "Core/Window.h"
#include <GLFW/glfw3.h>

using KeyState = std::pair<int, int>;
static std::map<int, KeyState> KeyMap;

// first : current
// second : previous

namespace co
{
	void Keyboard::GLFWKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode)
	{
		if (action == GLFW_REPEAT)
		{
			KeyMap[key].first = GLFW_PRESS;
			KeyMap[key].second = GLFW_PRESS;
			return;
		}

		KeyMap[key].second = KeyMap[key].first;
		KeyMap[key].first = action;
	}
	bool Keyboard::IsKeyDown(Key key)
	{
		int code = static_cast<int>(key);

		auto it = KeyMap.find(code);
		if (it != KeyMap.end())
		{
			return KeyMap.at(code).first == GLFW_PRESS;
		}
		// If the key is not registered yet - it means it was not pressed before, so we can add the key as fully released one.
		else
		{
			KeyMap[code].first = GLFW_RELEASE;
			KeyMap[code].second = GLFW_RELEASE;

			return false;
		}
	}
	bool Keyboard::IsKeyUp(Key key)
	{
		int code = static_cast<int>(key);

		auto it = KeyMap.find(code);
		if (it != KeyMap.end())
		{
			auto& state = KeyMap.at(code);
			return state.first == GLFW_RELEASE;
		}
		else
		{
			KeyMap[code].first = GLFW_RELEASE;
			KeyMap[code].second = GLFW_RELEASE;

			return false;
		}
	}
	bool Keyboard::IsKeyPressed(Key key)
	{
		int code = static_cast<int>(key);

		auto it = KeyMap.find(code);
		if (it != KeyMap.end())
		{
			auto& state = KeyMap.at(code);

			if ((state.first == GLFW_PRESS) && (state.second == GLFW_RELEASE))
			{
				state.first = GLFW_RELEASE;
				return true;
			}
			return false;
		}
		else
		{
			KeyMap[code].first = GLFW_RELEASE;
			KeyMap[code].second = GLFW_RELEASE;

			return false;
		}
	}
	bool Keyboard::IsKeyReleased(Key key)
	{
		int code = static_cast<int>(key);

		auto it = KeyMap.find(code);
		if (it != KeyMap.end())
		{
			auto& state = KeyMap.at(code);

			if ((state.first == GLFW_RELEASE) && (state.second == GLFW_PRESS))
			{
				state.second = GLFW_RELEASE;
				return true;
			}
			return false;
		}
		else
		{
			KeyMap[code].first = GLFW_RELEASE;
			KeyMap[code].second = GLFW_RELEASE;

			return false;
		}
	}
}