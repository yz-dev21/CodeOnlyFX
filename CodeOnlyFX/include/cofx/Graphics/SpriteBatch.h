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
		bool m_InPair;
	public:
		SpriteBatch();

		void Begin(Shader* shader);
		void Begin(Shader* shader, const Transform& transform);
		void Draw(Texture* texture, const Vec2f& position, const Vec2f& size, const Color& color, float rotate);
		void End();
	};
}
