#pragma once

#include <string>
#include <utility>
#include "../Graphics/Color.h"
#include "../System/Vector2.h"
#include "ContextSettings.h"

struct GLFWwindow;
struct GLFWmonitor;

namespace co
{
	class Window
	{
	private:
		Vec2u m_Position;
		Vec2u m_Size;
		std::string m_Title;
		ContextSettings m_Context;

		bool m_FullScreen;
		bool m_Resizable;

		GLFWwindow* m_Window;
		GLFWmonitor* m_Monitor;
	public:
		Window();
		Window(const ContextSettings& contextSettings);
		~Window();

		GLFWwindow* GetRawWindow() const;

		Vec2u GetPosition() const;
		void SetPosX(unsigned int x);
		void SetPosY(unsigned int y);
		void SetPosition(unsigned int x, unsigned int y);

		Vec2u GetSize() const;
		void SetWidth(unsigned int width);
		void SetHeight(unsigned int height);
		void SetSize(unsigned int width, unsigned int height);

		const std::string& GetTitle() const;
		void SetTitle(std::string_view title);

		void SetFullScreen(bool fullScreen);
		void SetResizable(bool resizable);

		void Clear(const Color& color);
		std::string_view GetHardWareInfo() const;
		void GetGLVersion(unsigned int& major, unsigned int& minor) const;

		void Close();
		bool IsRunning() const;
		void Update() const;
		void Cleanup();
	private:
		static void GLFWFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	};
}