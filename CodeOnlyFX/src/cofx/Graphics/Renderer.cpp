#include "Graphics/Renderer.h"
#include "../glm/mat4x4.hpp"
#include "../glm/ext/matrix_transform.hpp"
#include <GL/glew.h>

namespace co
{
	Shader* Renderer::m_Shader;
	unsigned int Renderer::m_QuadVAO;
	bool Renderer::m_InPair;

	void Renderer::Initialize()
	{
		m_Shader = nullptr;
		m_QuadVAO = NULL;
		m_InPair = false;

		unsigned int VBO;
		float vertices[] = {
			// pos      // tex
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &m_QuadVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(m_QuadVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void Renderer::Begin(Shader* shader)
	{
		m_Shader = shader;
		m_InPair = true;
	}
	void Renderer::Draw(const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate)
	{
		if (!m_InPair)
			return;

		m_Shader->Bind().SetUniform("useTex", false);
		glm::mat4 model = glm::mat4(1.0f);

		// Move
		model = glm::translate(model, glm::vec3(position, 0.0f));

		// Rotate
		if (rotate != 0.f)
		{
			model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));  // Move to center of quad
			model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move back to origin
		}

		// Scale
		model = glm::scale(model, glm::vec3(size, 1.0f));

		m_Shader->SetUniform("model", model);
		m_Shader->SetUniform("spriteColor", color);

		glBindVertexArray(m_QuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	void Renderer::Draw(Texture* texture, const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate)
	{
		if (!m_InPair)
			return;

		m_Shader->Bind().SetUniform("useTex", true);
		glm::mat4 model = glm::mat4(1.0f);

		// Move
		model = glm::translate(model, glm::vec3(position, 0.0f));

		// Rotate
		if (rotate != 0.f)
		{
			model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));  // Move to center of quad
			model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move back to origin
		}

		// Scale
		model = glm::scale(model, glm::vec3(size, 1.0f));

		m_Shader->SetUniform("model", model);
		m_Shader->SetUniform("spriteColor", color);

		glActiveTexture(GL_TEXTURE0);
		texture->Bind();

		glBindVertexArray(m_QuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	void Renderer::End()
	{
		m_InPair = false;
		m_Shader = nullptr;
	}
}