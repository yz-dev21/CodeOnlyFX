#pragma once

#include "Renderer.h"

namespace co
{
	class TextRenderer : public Renderer
	{
	public:
		TextRenderer();
		TextRenderer(Shader* shader);

		void DrawString();
	private:
	};
}