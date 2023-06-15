#pragma once

#include "Shader.h"
#include "Texture.h"
#include "../glm/vec2.hpp"

namespace co
{
	// 커스텀 렌더러, 스프라이트 렌더러, 텍스트 렌더러 등 여러 렌더링에 대한 작업을 한 클래스로 할지? 한다면 어떤 디자인으로 할지
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