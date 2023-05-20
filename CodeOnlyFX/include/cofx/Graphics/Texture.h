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
		std::vector<unsigned int> m_Image;
		glm::uvec2 m_Size;
	public:
		Texture();
		Texture(unsigned int width, unsigned int height, std::span<unsigned int> rawImage);
		Texture(const Texture& spriteSheet, const glm::uvec2& spriteSize, const glm::uvec2& position);

		~Texture();

		void Bind() const;
		void GenerateMipmap() const;

		const std::vector<unsigned int>& GetImage() const;
		const glm::uvec2& GetSize() const;

		void Cleanup();
	private:
		void GenerateTexture();
	};
}