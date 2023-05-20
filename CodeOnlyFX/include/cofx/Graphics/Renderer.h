#pragma once

#include "Shader.h"
#include "Texture.h"
#include "../Core/Window.h"

namespace co
{
	class Renderer
	{
	private:
		Shader m_Shader;
		unsigned int m_QuadVAO;
	public:
		// Create renderer using default shader.
		Renderer(const Window& window);

		void Draw(const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);
		void Draw(Texture& texture, const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);
	};
}