#pragma once

#include "Texture.h"
#include <vector>

namespace co
{
	class SpriteSheet
	{
	private:
		Texture* m_SpriteSheet;
	public:
		SpriteSheet(Texture* texture);

		Texture* GetRawSpriteSheet() const;
		void GetTexture(Texture& texture, unsigned int spriteSize, unsigned int x, unsigned int y);
	};
}