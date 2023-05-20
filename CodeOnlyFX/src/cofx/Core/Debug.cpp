#include "Core/Debug.h"
#include <iostream>
#include <Windows.h>
#include <GL/glew.h>

namespace co
{
	bool Debug::m_Init;
	bool Debug::Active = false;

	void Debug::Initialize()
	{
		if (!Active || m_Init) return;

#ifdef _WIN32
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwMode = NULL;
		GetConsoleMode(hOut, &dwMode);
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOut, dwMode);
#endif
		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(GLFWDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		m_Init = true;
	}
	void Debug::Critical(std::string_view str, const std::source_location& location)
	{
		if (!Active) return;

		std::cout << std::format("[\x1b[41mCRITICAL\x1b[0m] {}\nAt {}({}:{}) `{}`\n",
			str,
			location.file_name(),
			location.line(),
			location.column(),
			location.function_name())
			<< std::endl;
	}
	void Debug::Error(std::string_view str, const std::source_location& location)
	{
		if (!Active) return;

		std::cout << std::format("[\x1b[91mERROR\x1b[0m] {}\nAt {}({}:{}) `{}`\n",
			str,
			location.file_name(),
			location.line(),
			location.column(),
			location.function_name())
			<< std::endl;
	}
	void Debug::Warn(std::string_view str, const std::source_location& location)
	{
		if (!Active) return;

		std::cout << std::format("[\x1b[33mWARN\x1b[0m] {}\nAt {}({}:{}) `{}`\n",
			str,
			location.file_name(),
			location.line(),
			location.column(),
			location.function_name())
			<< std::endl;
	}
	void Debug::Info(std::string_view str, const std::source_location& location)
	{
		if (!Active) return;

		std::cout << std::format("[\x1b[94mINFO\x1b[0m] {}\nAt {}({}:{}) `{}`\n",
			str,
			location.file_name(),
			location.line(),
			location.column(),
			location.function_name())
			<< std::endl;
	}
	void Debug::GLFWDebugOutput(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam)
	{
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         CO_CRITICAL("OpenGL error ({}); {}", id, message); break;
		case GL_DEBUG_SEVERITY_MEDIUM:       CO_ERROR("OpenGL error ({}); {}", id, message);    break;
		case GL_DEBUG_SEVERITY_LOW:          CO_WARN("OpenGL error ({}); {}", id, message);     break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: CO_INFO("OpenGL error ({}); {}", id, message);     break;
		}
	}
}