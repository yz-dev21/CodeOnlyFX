#pragma once

#include "Color.h"
#include <string>
#include <utility>
#include "../Core/ContextSettings.h"

struct GLFWwindow;

namespace co
{
	class Window;

	class GraphicsDevice
	{
	private:
		Window* m_Window;
		std::pair<unsigned int, unsigned int> m_Version;
	public:
		GraphicsDevice();
		GraphicsDevice(Window* window, const ContextSettings& contextSettings);

		std::string_view GetHardwareInfo() const;
		const std::pair<unsigned int, unsigned int>& GetGLVersion() const;

		void Clear(const Color& color);
	private:
		static void GLFWFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	};
}