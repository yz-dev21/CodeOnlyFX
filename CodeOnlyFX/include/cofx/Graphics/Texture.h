#pragma once

#include <vector>
#include "../System/Vector2.h"
#include <span>

namespace co
{
	class Texture
	{
	private:
		unsigned int m_Texture;
		std::vector<unsigned char> m_Image;
		Vec2f m_Size;
	public:
		Texture();
		Texture(unsigned int width, unsigned int height, std::span<unsigned char> rawImage);
		~Texture();

		void Bind() const;
		void GenerateMipmap() const;

		const std::vector<unsigned char>& GetImage() const;
		Vec2f GetSize() const;

		void Cleanup();
	};
}