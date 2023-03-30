#pragma once

namespace co
{
	struct Color
	{
		unsigned int R{};
		unsigned int G{};
		unsigned int B{};
		unsigned int A{ 255 };

		inline Color(unsigned int r, unsigned int b, unsigned int g, unsigned int a = 255);

		inline unsigned int ToInt() const;

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