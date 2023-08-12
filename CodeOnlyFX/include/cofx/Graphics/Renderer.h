#pragma once

#include "Shader.h"

namespace co
{
	class Renderer
	{
	protected:
		Shader* m_Shader;

		uint32_t m_QuadVAO;

		virtual void Initialize() = 0;
	public:
		Renderer() : m_Shader(nullptr), m_QuadVAO(NULL) { }
		Renderer(Shader* shader) : m_Shader(shader), m_QuadVAO(NULL) { }
	};
}