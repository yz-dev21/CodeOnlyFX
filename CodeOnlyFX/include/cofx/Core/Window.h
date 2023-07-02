#pragma once

#include <string>
#include <utility>
#include "../Graphics/Color.h"
#include "../glm/vec2.hpp"
#include "Input/Keyboard.h"

struct GLFWwindow;
struct GLFWmonitor;

namespace co
{
	class Window
	{
	private:
		glm::uvec2 m_Position;
		glm::uvec2 m_Size;
		std::string m_Title;

		bool m_FullScreen;
		bool m_Resizable;
		uint32_t m_FrameRate;

		GLFWwindow* m_Window;
		GLFWmonitor* m_Monitor;
	public:
		Window();
		Window(uint32_t width, uint32_t height, std::string_view title);
		~Window();

		const glm::uvec2& GetPosition() const;
		void SetPosX(uint32_t x);
		void SetPosY(uint32_t y);
		void SetPosition(uint32_t x, uint32_t y);

		const glm::uvec2& GetSize() const;
		void SetWidth(uint32_t width);
		void SetHeight(uint32_t height);
		void SetSize(uint32_t width, uint32_t height);

		const std::string& GetTitle() const;
		void SetTitle(std::string_view title);

		void SetFullScreen(bool fullScreen);
		void SetResizable(bool resizable);

		void SetVsync(bool vsync) const;

		void Clear(const Color& color) const;
		std::string_view GetHardWareInfo() const;

		void Close() const;
		bool IsRunning() const;
		void Update();
		void Cleanup() const;
	private:
		static void GLFWFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	};
}