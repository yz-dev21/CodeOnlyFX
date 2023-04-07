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
		void Draw(Texture* texture, const Vec2f& position, const Vec2f& size, const Color& color, float rotate);
		void End();
	};
}