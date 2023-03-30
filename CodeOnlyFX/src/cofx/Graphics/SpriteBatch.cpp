#include "Graphics/SpriteBatch.h"
#include "Graphics/Transform.h"
#include <GL/glew.h>

namespace co
{
	SpriteBatch::SpriteBatch() : m_Shader(nullptr), m_QuadVAO(NULL)
	{
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
	void SpriteBatch::Begin(Shader* shader)
	{
		m_Shader = shader;
	}
	void SpriteBatch::Draw(Texture* texture, const Vec2f& position, const Vec2f& size, const Color& color, float rotate)
	{
		m_Shader->Bind();
		Transform model;

		// Move
		model.Translate(position);

		// Rotate
		//if (rotate.ToDegrees() != 0.f)
		//{
		//	model.Translate(cu::Vector2f(0.5f * size.X, 0.5f * size.Y)); // Move to center of quad
		//	// model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
		//	model.Translate(cu::Vector2f(-0.5f * size.X, -0.5f * size.Y)); // Move back to origin
		//}

		// Scale
		if (size == Vec2f::Zero)
			model.Scale(texture->GetSize());
		else
			model.Scale(size);

		m_Shader->SetUniform("model", model);

		glActiveTexture(GL_TEXTURE0);
		texture->Bind();

		glBindVertexArray(m_QuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	void SpriteBatch::End()
	{
		m_Shader = nullptr;
	}
}