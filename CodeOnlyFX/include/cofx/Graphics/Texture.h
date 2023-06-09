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
		std::vector<uint32_t> m_Image;
		glm::uvec2 m_Size;
	public:
		Texture();
		Texture(uint32_t width, uint32_t height, std::span<uint32_t> rawImage);
		Texture(const Texture& spriteSheet, uint32_t spriteSize, const glm::uvec2& spritePos);

		~Texture();

		Texture& Create();
		void Bind() const;
		void GenerateMipmap() const;

		const std::vector<uint32_t>& GetImage() const;
		const glm::uvec2& GetSize() const;

		void Cleanup();
	};
}