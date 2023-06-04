#include "Graphics/Animation.h"

namespace co
{
	Animation::Animation(const Texture& spriteSheet, const glm::uvec2& spriteSize, const glm::uvec2& from, const glm::uvec2& to)
	{
		const int xp = from.x * spriteSize.x, yp = from.y * spriteSize.y;

		for (auto ty = 0; ty < spriteSize.y; ty++)
		{
			for (auto tx = 0; tx < spriteSize.x; tx++)
			{
				auto i = (xp + tx) + (yp + ty) * spriteSheet.GetSize().x;
				unsigned int pixel = spriteSheet.GetImage()[i];
				m_Image.push_back(pixel);
			}
		}
	}
}