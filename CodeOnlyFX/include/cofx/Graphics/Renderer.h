#pragma once

#include "Shader.h"
#include "Texture.h"
#include "../glm/vec2.hpp"

namespace co
{
	class Renderer
	{
	private:
		Shader m_Shader;
		uint32_t m_QuadVAO;
	public:
		Renderer(const glm::uvec2& windowSize);

		void Draw(const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);
		void Draw(Texture& texture, const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);
	};
}