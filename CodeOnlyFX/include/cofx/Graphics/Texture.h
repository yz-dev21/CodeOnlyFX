#pragma once

#include "Image.h"

namespace co
{
	class Texture
	{
	private:
		uint32_t m_Texture;
		Image m_Image;
	public:
		Texture(const Image& image);
		Texture(const Image& spriteSheet, uint32_t spriteSize, const glm::uvec2& spritePos);

		~Texture();

		void Bind() const;
		void GenerateMipmap() const;

		const Image& GetImage() const;

		void Cleanup();
	private:
		void Create();
	};
}