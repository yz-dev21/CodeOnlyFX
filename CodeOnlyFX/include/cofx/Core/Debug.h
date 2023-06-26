#pragma once

#include <string>
#include <format>
#include <source_location>

#define CO_CRITICAL(fmt, ...) co::Debug::Critical(std::format(fmt, ##__VA_ARGS__));
#define CO_ERROR(fmt, ...) co::Debug::Error(std::format(fmt, ##__VA_ARGS__));
#define CO_WARN(fmt, ...) co::Debug::Warn(std::format(fmt, ##__VA_ARGS__));
#define CO_INFO(fmt, ...) co::Debug::Info(std::format(fmt, ##__VA_ARGS__));

namespace co
{
	class Debug
	{
	private:
		static bool m_Init;

		Debug();
	public:
		static bool Active;

		static void Initialize();
		static void Critical(std::string_view str, const std::source_location& location = std::source_location::current());
		static void Error(std::string_view str, const std::source_location& location = std::source_location::current());
		static void Warn(std::string_view str, const std::source_location& location = std::source_location::current());
		static void Info(std::string_view str, const std::source_location& location = std::source_location::current());
	private:
		static void __stdcall GLFWDebugOutput(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int length, const char* message, const void* userParam);
	};
}