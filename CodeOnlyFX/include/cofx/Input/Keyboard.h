#pragma once

#include <map>
#include "../Core/Window.h"

namespace co
{
	enum class Key : int
	{
		Zero = 48,
		One = 49,
		Two = 50,
		Three = 51,
		Four = 52,
		Five = 53,
		Six = 54,
		Seven = 55,
		Eight = 56,
		Nine = 57,
		Num0 = 320,
		Num1 = 321,
		Num2 = 322,
		Num3 = 323,
		Num4 = 324,
		Num5 = 325,
		Num6 = 326,
		Num7 = 327,
		Num8 = 328,
		Num9 = 329,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		Escape = 256,
		Space = 32,
		Apostrophe = 39,
		Comma = 44,
		Minus = 45,
		Period = 46,
		Slash = 47,
		Backslash = 92,
		Semicolon = 59,
		Equal = 61,
		LeftBracket = 91,
		RightBracket = 93,
	};

	class Keyboard
	{
	private:
		Keyboard();
		static void GLFWKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode);

		friend class Window;
	public:
		static bool IsKeyHeld(Key key);
		static bool IsKeyPressed(Key key);
		static bool IsKeyReleased(Key key);
	};
}