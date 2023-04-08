#pragma once

#include "Shader.h"
#include "Texture.h"

namespace co
{
	class SpriteBatch
	{
	private:
		Shader* m_Shader;
		unsigned int m_QuadVAO;
		bool m_InPair;
	public:
		SpriteBatch();

		void Begin(Shader* shader);
		void Draw(Texture* texture, const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);
		void End();
	};
}