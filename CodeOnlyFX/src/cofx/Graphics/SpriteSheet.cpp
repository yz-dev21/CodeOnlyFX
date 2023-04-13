#include "Graphics/SpriteSheet.h"

namespace co
{
	SpriteSheet::SpriteSheet(Texture* spriteSheet) : m_SpriteSheet(spriteSheet)
	{
	}
	Texture* SpriteSheet::GetRawSpriteSheet() const
	{
		return m_SpriteSheet;
	}
	void SpriteSheet::GetTexture(Texture& texture, unsigned int spriteSize, unsigned int x, unsigned int y)
	{
		int xp = x * spriteSize, yp = y * spriteSize;
		const auto& size = texture.GetSize();
		int xt = (size.x - spriteSize) / 2, yt = (size.y - spriteSize) / 2;

		for (auto ty = 0; ty < spriteSize; ty++)
		{
			for (auto tx = 0; tx < spriteSize; tx++)
			{
				size_t index = (xp + tx) + (yp + ty) * m_SpriteSheet->GetSize().x;
				unsigned char color = m_SpriteSheet->GetImage()[index];
				texture[index] = color;
			}
		}
	}
}
