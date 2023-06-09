#include "Graphics/Texture.h"
#include "Core/Debug.h"
#include <GL/glew.h>

namespace co
{
	Texture::Texture() : m_Texture(NULL), m_Size(0, 0)
	{
	}
	Texture::Texture(uint32_t width, uint32_t height, std::span<uint32_t> rawImage) : m_Texture(NULL), m_Size(width, height)
	{
		m_Image.assign(rawImage.begin(), rawImage.end());
	}
	Texture::Texture(const Texture& spriteSheet, uint32_t spriteSize, const glm::uvec2& spritePos) : m_Texture(NULL), m_Size(spriteSize, spriteSize)
	{
		const int xp = spritePos.x * spriteSize, yp = spritePos.y * spriteSize;

		for (auto ty = 0; ty < spriteSize; ty++)
		{
			for (auto tx = 0; tx < spriteSize; tx++)
			{
				auto i = (xp + tx) + (yp + ty) * spriteSheet.GetSize().x;
				m_Image.push_back(spriteSheet.GetImage()[i]);
			}
		}
	}
	Texture::~Texture()
	{
		Cleanup();
	}
	Texture& Texture::Create()
	{
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Size.x, m_Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image.data());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		return *this;
	}
	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}
	void Texture::GenerateMipmap() const
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	const std::vector<uint32_t>& Texture::GetImage() const
	{
		return m_Image;
	}
	const glm::uvec2& Texture::GetSize() const
	{
		return m_Size;
	}
	void Texture::Cleanup()
	{
		if (m_Texture)
			glDeleteTextures(1, &m_Texture);
	}
}