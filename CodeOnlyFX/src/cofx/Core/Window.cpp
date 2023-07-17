// Keyboard.h includes Window.h
#include "Input/Keyboard.h"
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
	Window::Window()
		: m_Position(0, 0), m_Size(0, 0), m_FullScreen(false), m_Resizable(true), m_FrameRate(0), m_Window(nullptr), m_Monitor(nullptr)
	{
	}
	Window::Window(uint32_t width, uint32_t height, std::string_view title)
		: m_Position(50, 50), m_Size(width, height), m_Title(title), m_FullScreen(false), m_Resizable(true), m_FrameRate(0), m_Window(nullptr), m_Monitor(nullptr)
	{
		if (!glfwInit())
		{
			Debug::Critical("cofx::Core::Window; Failed to initialize GLFW.");
			return;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, Debug::Active);

		m_Monitor = glfwGetPrimaryMonitor();

		m_Window = glfwCreateWindow(m_Size.x, m_Size.y, m_Title.c_str(), m_FullScreen ? m_Monitor : nullptr, nullptr);
		if (m_Window == nullptr)
		{
			Debug::Critical("cofx::Core::Window; Failed to create GLFWwindow.");
			return;
		}
		glfwSetWindowPos(m_Window, m_Position.x, m_Position.y);

		glfwMakeContextCurrent(m_Window);

		glfwFocusWindow(m_Window);

		glfwSetWindowUserPointer(m_Window, this);

		glewExperimental = GL_TRUE;
		GLenum result = glewInit();
		if (result != GLEW_OK)
		{
			CO_CRITICAL("cofx::Core::Window; Failed to initialize GLEW. {}", (const char*)glewGetErrorString(result));
			return;
		}
		glfwSetFramebufferSizeCallback(m_Window, GLFWFrameBufferSizeCallback);
		glfwSetKeyCallback(m_Window, Keyboard::GLFWKeyCallback);
	}
	Window::~Window()
	{
		Cleanup();
	}
	const glm::uvec2& Window::GetPosition() const
	{
		return m_Position;
	}
	void Window::SetPosX(uint32_t x)
	{
		if (m_Position.x == x) return;

		m_Position.x = x;
		glfwSetWindowPos(m_Window, m_Position.x, m_Position.y);
	}
	void Window::SetPosY(uint32_t y)
	{
		if (m_Position.y == y) return;

		m_Position.x = y;
		glfwSetWindowPos(m_Window, m_Position.x, m_Position.y);
	}
	void Window::SetPosition(uint32_t x, uint32_t y)
	{
		if (m_Position.x == x && m_Position.y == y) return;

		m_Position = { x, y };
		glfwSetWindowPos(m_Window, m_Position.x, m_Position.y);
	}
	const glm::uvec2& Window::GetSize() const
	{
		return m_Size;
	}
	void Window::SetWidth(uint32_t width)
	{
		if (m_Size.x == width) return;

		m_Size.x = width;
		glfwSetWindowSize(m_Window, m_Size.x, m_Size.y);
	}
	void Window::SetHeight(uint32_t height)
	{
		if (m_Size.y == height) return;

		m_Size.y = height;
		glfwSetWindowSize(m_Window, m_Size.x, m_Size.y);
	}
	void Window::SetSize(uint32_t width, uint32_t height)
	{
		if (m_Size.x == width && m_Size.y == height) return;

		m_Size = { width, height };
		glfwSetWindowSize(m_Window, m_Size.x, m_Size.y);
	}
	const std::string& Window::GetTitle() const
	{
		return m_Title;
	}
	void Window::SetTitle(std::string_view title)
	{
		if (m_Title == title) return;

		m_Title = title;
		glfwSetWindowTitle(m_Window, m_Title.c_str());
	}
	void Window::SetFullScreen(bool fullScreen)
	{
		if (m_FullScreen == fullScreen) return;

		m_FullScreen = fullScreen;
		if (m_FullScreen)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(m_Monitor);
			glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
		}
		else
		{
			glfwSetWindowMonitor(m_Window, nullptr, m_Position.x, m_Position.y, m_Size.x, m_Size.y, 0);
			SetResizable(true);
		}
	}
	void Window::SetResizable(bool resizable)
	{
		if (m_Resizable == resizable) return;

		m_Resizable = resizable;
		glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, m_Resizable);
	}
	void Window::SetVsync(bool vsync) const
	{
		glfwSwapInterval(static_cast<int>(vsync));
	}
	void Window::Clear(const Color& color) const
	{
		glClearColor(static_cast<float>(color.R / 255.f), static_cast<float>(color.G / 255.f), static_cast<float>(color.B / 255.f), static_cast<float>(color.A / 255.f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	std::string_view Window::GetHardWareInfo() const
	{
		auto renderer = (const char*)glGetString(GL_RENDERER);
		return renderer;
	}
	void Window::Close() const
	{
		glfwSetWindowShouldClose(m_Window, true);
	}
	bool Window::IsRunning() const
	{
		return !glfwWindowShouldClose(m_Window);
	}
	void Window::Update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
	void Window::Cleanup() const
	{
		if (m_Window)
		{
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}
	}
	void Window::GLFWFrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (!self.m_FullScreen)
		{
			self.m_Size = { width, height };
		}
		glViewport(0, 0, width, height);
	}
}
