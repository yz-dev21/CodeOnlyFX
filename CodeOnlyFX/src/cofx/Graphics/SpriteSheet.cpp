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
		const int xp = x * spriteSize, yp = y * spriteSize;

		std::vector<unsigned int> image;

		for (auto ty = 0; ty < spriteSize; ty++)
		{
			for (auto tx = 0; tx < spriteSize; tx++)
			{
				auto i = (xp + tx) + (yp + ty) * m_SpriteSheet->GetSize().x;
				unsigned int pixel = m_SpriteSheet->GetImage()[i];
				image.push_back(pixel);
			}
		}
		texture = Texture(spriteSize, spriteSize, image);
	}
}
