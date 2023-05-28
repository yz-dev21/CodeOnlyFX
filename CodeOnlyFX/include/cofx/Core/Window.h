#pragma once

#include <string>
#include <utility>
#include "../Graphics/Color.h"
#include "../glm/vec2.hpp"

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

		GLFWwindow* m_Window;
		GLFWmonitor* m_Monitor;
	public:
		Window();
		Window(unsigned int width, unsigned int height, std::string_view title);
		~Window();

		const glm::uvec2& GetPosition() const;
		void SetPosX(unsigned int x);
		void SetPosY(unsigned int y);
		void SetPosition(unsigned int x, unsigned int y);

		const glm::uvec2& GetSize() const;
		void SetWidth(unsigned int width);
		void SetHeight(unsigned int height);
		void SetSize(unsigned int width, unsigned int height);

		const std::string& GetTitle() const;
		void SetTitle(std::string_view title);

		void SetFullScreen(bool fullScreen);
		void SetResizable(bool resizable);

		void SetVsync(bool vsync);

		void Clear(const Color& color);
		std::string_view GetHardWareInfo() const;

		void Close();
		bool IsRunning() const;
		void Update() const;
		void Cleanup();
	private:
		static void GLFWFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	};
}