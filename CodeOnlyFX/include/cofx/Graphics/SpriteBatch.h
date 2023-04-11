#pragma once

#include "Shader.h"
#include "Texture.h"
#include "../Core/Window.h"

namespace co
{
	class SpriteBatch
	{
	private:
		Window* m_Window;
		Shader* m_Shader;
		unsigned int m_QuadVAO;
		bool m_InPair;
	public:
		SpriteBatch(Window* window);

		void Begin(Shader* shader);
		void Draw(Texture* texture, const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);
		void End();
	};
}