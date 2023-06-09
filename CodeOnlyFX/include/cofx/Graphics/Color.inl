namespace co
{
	Color::Color(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
		: R(r), G(g), B(b), A(a)
	{
	}
	uint32_t Color::ToInt() const
	{
		return static_cast<uint32_t>((R << 24) | (G << 16) | (B << 8) | A);
	}
	inline const Color Color::Black(0, 0, 0);
	inline const Color Color::White(255, 255, 255);
	inline const Color Color::Red(255, 0, 0);
	inline const Color Color::Green(0, 255, 0);
	inline const Color Color::Blue(0, 0, 255);
	inline const Color Color::Yellow(255, 255, 0);
	inline const Color Color::Magenta(255, 0, 255);
	inline const Color Color::Cyan(0, 255, 255);
	inline const Color Color::Transparent(0, 0, 0, 0);
}