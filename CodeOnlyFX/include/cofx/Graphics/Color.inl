namespace co
{
	Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
		: R(r), G(g), B(b), A(a)
	{
	}
	unsigned int Color::ToInt() const
	{
		return static_cast<unsigned int>((R << 24) | (G << 16) | (B << 8) | A);
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