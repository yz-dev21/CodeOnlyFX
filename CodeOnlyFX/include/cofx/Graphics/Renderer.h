#pragma once

#include "Shader.h"
#include "Texture.h"

namespace co
{
	class Renderer
	{
	private:
		static Shader* m_Shader;
		static unsigned int m_QuadVAO;
		static bool m_InPair;
	public:
		static void Initialize();
		static void Begin(Shader* shader);

		static void Draw(const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);
		static void Draw(Texture* texture, const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);

		static void End();
	};
}