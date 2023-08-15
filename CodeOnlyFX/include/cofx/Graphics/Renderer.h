#pragma once

#include "Shader.h"
#include "../Core/Debug.h"

namespace co
{
	class Renderer
	{
	protected:
		Shader* m_Shader;
		uint32_t m_QuadVAO;

		bool m_Pair;

		static uint32_t m_InitCode;

		virtual void Initialize() = 0;

		Renderer() : m_Shader(nullptr), m_QuadVAO(NULL), m_Pair(false) { }
		Renderer(Shader* shader) : m_Shader(shader), m_QuadVAO(NULL), m_Pair(false) { }
	public:
		virtual void Begin(/* Camera, Scene, Matrix etc. */) = 0;
		void End()
		{
			m_Pair = false;
		}
	};
}