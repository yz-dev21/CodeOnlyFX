#pragma once

#include "Texture.h"
#include "../glm/vec2.hpp"

namespace co
{
	class Animation
	{
	private:
		std::vector<Texture> m_Textures;
	public:
		Animation(const Texture& spriteSheet, const glm::uvec2& spriteSize, const glm::uvec2& from, const glm::uvec2& to);

		void Play(Texture& texture);
	};
}