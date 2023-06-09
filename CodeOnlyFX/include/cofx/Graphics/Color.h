#pragma once

namespace co
{
	struct Color
	{
		uint32_t R{};
		uint32_t G{};
		uint32_t B{};
		uint32_t A{ 255 };

		inline Color(uint32_t r, uint32_t b, uint32_t g, uint32_t a = 255);

		inline uint32_t ToInt() const;

		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;
		static const Color Transparent;
	};
}
#include "Color.inl"