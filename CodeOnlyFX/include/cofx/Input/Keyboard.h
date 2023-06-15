#pragma once

struct GLFWwindow;

namespace co
{
	// 입력 또한 윈도우와 관련이 있는 부분인데, 연결 지어 코딩 하는 것이 불가능할까?
	class Keyboard
	{
	public:
		Keyboard() = delete;

		static void Initialize(GLFWwindow* window);

		static bool IsKeyHeld();
		static bool IsKeyPressed();
		static bool IsKeyReleased();
	};
}