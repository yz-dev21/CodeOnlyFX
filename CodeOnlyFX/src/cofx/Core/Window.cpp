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
	Window::Window()
		: m_Position(0, 0), m_Size(0, 0), m_FullScreen(false), m_Resizable(true), m_Window(nullptr), m_Monitor(nullptr)
	{
	}
	Window::Window(const ContextSettings& contextSettings)
		: m_Position(50, 50), m_Size(800, 600), m_Title("COFX App"), m_Context(contextSettings), m_FullScreen(false), m_Resizable(true), m_Window(nullptr), m_Monitor(nullptr)
	{
		if (!glfwInit())
		{
			Debug::Critical("cofx::Core::Window; Failed to initialize GLFW.");
			return;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_Context.OpenGLMajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_Context.OpenGLMinorVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, m_Context.Debug);

		m_Monitor = glfwGetPrimaryMonitor();

		m_Window = glfwCreateWindow(m_Size.X, m_Size.Y, m_Title.c_str(), m_FullScreen ? m_Monitor : nullptr, nullptr);
		if (m_Window == nullptr)
		{
			Debug::Critical("cofx::Core::Window; Failed to create GLFWwindow.");
			return;
		}
		glfwSetWindowPos(m_Window, m_Position.X, m_Position.Y);

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
	}
	Window::~Window()
	{
		Cleanup();
	}
	GLFWwindow* Window::GetRawWindow() const
	{
		return m_Window;
	}
	Vec2u Window::GetPosition() const
	{
		return m_Position;
	}
	void Window::SetPosX(unsigned int x)
	{
		if (m_Position.X == x) return;

		m_Position.X = x;
		glfwSetWindowPos(m_Window, m_Position.X, m_Position.Y);
	}
	void Window::SetPosY(unsigned int y)
	{
		if (m_Position.Y == y) return;

		m_Position.Y = y;
		glfwSetWindowPos(m_Window, m_Position.X, m_Position.Y);
	}
	void Window::SetPosition(unsigned int x, unsigned int y)
	{
		if (m_Position.X == x && m_Position.Y == y) return;

		m_Position.X = x;
		m_Position.Y = y;
		glfwSetWindowPos(m_Window, m_Position.X, m_Position.Y);
	}
	Vec2u Window::GetSize() const
	{
		return m_Size;
	}
	void Window::SetWidth(unsigned int width)
	{
		if (m_Size.X == width) return;

		m_Size.X = width;
		glfwSetWindowSize(m_Window, m_Size.X, m_Size.Y);
	}
	void Window::SetHeight(unsigned int height)
	{
		if (m_Size.Y == height) return;

		m_Size.Y = height;
		glfwSetWindowSize(m_Window, m_Size.X, m_Size.Y);
	}
	void Window::SetSize(unsigned int width, unsigned int height)
	{
		if (m_Size.X != width)
			m_Size.X = width;

		if (m_Size.Y != height)
			m_Size.Y = height;

		if (m_Size.X != width || m_Size.Y != height)
			glfwSetWindowSize(m_Window, m_Size.X, m_Size.Y);
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
			glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, mode->width, mode->height, 0);
		}
		else
		{
			glfwSetWindowMonitor(m_Window, nullptr, m_Position.X, m_Position.Y, m_Size.X, m_Size.Y, 0);
			SetResizable(true);
		}
	}
	void Window::SetResizable(bool resizable)
	{
		if (m_Resizable == resizable) return;

		m_Resizable = resizable;
		glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, m_Resizable);
	}
	void Window::Clear(const Color& color)
	{
		glClearColor(static_cast<float>(color.R / 255.f), static_cast<float>(color.G / 255.f), static_cast<float>(color.B / 255.f), static_cast<float>(color.A / 255.f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Advanced?
	}
	std::string_view Window::GetHardWareInfo() const
	{
		auto renderer = (const char*)glGetString(GL_RENDERER);
		return renderer;
	}
	void Window::GetGLVersion(unsigned int& major, unsigned int& minor) const
	{
		major = m_Context.OpenGLMajorVersion;
		minor = m_Context.OpenGLMinorVersion;
	}
	void Window::Close()
	{
		glfwSetWindowShouldClose(m_Window, true);
	}
	bool Window::IsRunning() const
	{
		return !glfwWindowShouldClose(m_Window);
	}
	void Window::Update() const
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
	void Window::Cleanup()
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
			self.m_Size.X = width;
			self.m_Size.Y = height;
		}
		glViewport(0, 0, width, height);
	}
}
