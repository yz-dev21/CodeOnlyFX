#pragma once

#include "Shader.h"
#include "Texture.h"

namespace co
{
	class Renderer
	{
	private:
		static Shader* m_Shader;
		static uint32_t m_QuadVAO;
		static bool m_Init;
		static bool m_Pair;
	public:
		static void Begin();
		static void Begin(Shader* shader);

		static void End();

		static void DrawRect(const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);
		static void Draw(const Texture& target, const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);
		static void DrawString(/* rendering texts */);
	private:
		Renderer();

		static void Initialize();
		static void AssignDefaultShader();
	};
}