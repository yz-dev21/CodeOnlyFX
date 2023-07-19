#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Core/Debug.h"
#include <GL/glew.h>

namespace co
{
	Texture::Texture(const Image& image) : m_Texture(NULL), m_Image(image)
	{
		Create();
	}
	Texture::Texture(const Image& spriteSheet, uint32_t spriteSize, const glm::uvec2& spritePos) : m_Texture(NULL)
	{
		m_Image.Size = { spriteSize, spriteSize };

		const int xp = spritePos.x * spriteSize, yp = spritePos.y * spriteSize;

		for (auto ty = 0; ty < spriteSize; ty++)
		{
			for (auto tx = 0; tx < spriteSize; tx++)
			{
				auto i = (xp + tx) + (yp + ty) * spriteSheet.Size.x;
				m_Image.Data.push_back(spriteSheet.Data[i]);
			}
		}
		Create();
	}
	Texture::~Texture()
	{
		Cleanup();
	}
	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}
	void Texture::GenerateMipmap() const
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	const Image& Texture::GetImage() const
	{
		return m_Image;
	}
	void Texture::Draw(const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate)
	{
		Renderer::Draw(*this, position, size, color, rotate);
	}
	void Texture::Cleanup()
	{
		if (m_Texture)
			glDeleteTextures(1, &m_Texture);
	}
	void Texture::Create()
	{
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Image.Size.x, m_Image.Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image.Data.data());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}