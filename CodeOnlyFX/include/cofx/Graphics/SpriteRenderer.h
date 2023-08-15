#pragma once

#include "Renderer.h"
#include "Texture.h"
#include <string>

namespace co
{
	class SpriteRenderer : public Renderer
	{
	public:
		SpriteRenderer();
		SpriteRenderer(Shader* shader);

		void Begin() override;

		void Draw(const Texture& target, const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate);
		void Draw(const Texture& target, const glm::vec2& position);
	private:
		void Initialize() override;
	};
}