#pragma once

#include <vector>
#include "../glm/vec2.hpp"
#include <span>

namespace co
{
	class Texture
	{
	private:
		unsigned int m_Texture;
		std::vector<unsigned char> m_Image;
		glm::uvec2 m_Size;
	public:
		Texture();
		Texture(unsigned int width, unsigned int height, std::span<unsigned char> rawImage);
		~Texture();

		void Bind() const;
		void GenerateMipmap() const;

		const std::vector<unsigned char>& GetImage() const;
		const glm::uvec2& GetSize() const;

		unsigned char& operator[](int index);

		void Cleanup();
	};
}