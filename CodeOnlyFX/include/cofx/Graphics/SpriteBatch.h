#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

namespace co
{
	class SpriteBatch
	{
	private:
		Shader* m_Shader;
		unsigned int m_QuadVAO;
	public:
		SpriteBatch();

		void Begin(Shader* shader);
		void Draw(Texture* texture, const Vec2f& position, const Vec2f& size, const Color& color, float rotate);
		void End();
	};
}