#pragma once

#include "Image.h"
#include <glm/vec2.hpp>
#include "../Graphics/Color.h"

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

		void Draw(const glm::vec2& position);
		void Draw(const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);

		void Cleanup();
	private:
		void Create();
	};
}