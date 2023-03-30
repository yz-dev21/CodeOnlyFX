#include "Graphics/GraphicsDevice.h"
#include "Core/Window.h"
#include "Core/Debug.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

namespace co
{
	GraphicsDevice::GraphicsDevice() : m_Window(nullptr), m_Version(0, 0)
	{
	}
	GraphicsDevice::GraphicsDevice(Window* window, const ContextSettings& contextSettings) : m_Window(window)
	{
		m_Version = std::make_pair(contextSettings.OpenGLMajorVersion, contextSettings.OpenGLMinorVersion);

		glewExperimental = GL_TRUE;

		GLenum result = glewInit();
		if (result != GLEW_OK)
		{
			CO_CRITICAL("Femto::Graphics::GraphicsDevice; Failed to initialize GLEW. {}", (const char*)glewGetErrorString(result));
			return;
		}
		glfwSetFramebufferSizeCallback(m_Window->GetRawWindow(), GLFWFrameBufferSizeCallback);
	}
	void GraphicsDevice::Clear(const Color& color)
	{
		glClearColor(static_cast<float>(color.R), static_cast<float>(color.G), static_cast<float>(color.B), static_cast<float>(color.A));
		glClear(GL_COLOR_BUFFER_BIT); // Advanced?
	}
	std::string_view GraphicsDevice::GetHardwareInfo() const
	{
		auto renderer = (const char*)glGetString(GL_RENDERER);
		return renderer;
	}
	const std::pair<unsigned int, unsigned int>& GraphicsDevice::GetGLVersion() const
	{
		return m_Version;
	}
	void GraphicsDevice::GLFWFrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}