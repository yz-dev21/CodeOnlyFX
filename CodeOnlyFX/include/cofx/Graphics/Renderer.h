#pragma once

#include "Shader.h"
#include "Texture.h"
#include "../Core/Window.h"

namespace co
{
	class Renderer
	{
	private:
		static Shader* m_Shader;
		static unsigned int m_QuadVAO;
		static bool m_InPair;
		static bool m_Init;
	public:
		// Use default shader.
		static void Initialize(const Window& window);
		// Use custom shader.
		static void Initialize(Shader* shader);

		static void Begin();

		static void Draw(const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);
		static void Draw(Texture* texture, const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);

		static void End();
	};
}