#pragma once

#include "Color.h"
#include "../glm/vec2.hpp"

namespace co
{
	class Drawable
	{
	public:
		virtual void Bind() const = 0;
		virtual void Draw(const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate) = 0;
	};
}