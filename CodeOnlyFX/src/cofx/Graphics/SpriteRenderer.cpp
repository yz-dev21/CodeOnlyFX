#include "Graphics/SpriteRenderer.h"
#include "Core/Debug.h"
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace co
{
	SpriteRenderer::SpriteRenderer() : Renderer()
	{
		m_Shader = new Shader();

		// Add default vertex shader.
		const std::string vertexCode = R"(
#version 330 core
layout (location = 0) in vec4 coVertex;

out vec2 coTexCoords;

uniform mat4 coModel;
uniform mat4 coProjection;

void main()
{
	coTexCoords = coVertex.zw;
	gl_Position = coProjection * coModel * vec4(coVertex.xy, 0.0, 1.0);
}
)";
		m_Shader->Attach(vertexCode, ShaderType::Vertex);

		// Add default fragment shader.
		const std::string fragmentCode = R"(
#version 330 core
in vec2 coTexCoords;
out vec4 coColor;

uniform sampler2D coImage;
uniform vec3 coSpriteColor;

void main()
{
	coColor = vec4(coSpriteColor, 1.0) * texture(coImage, coTexCoords);
	if (coColor.a == 0)
		discard;
}
)";
		m_Shader->Attach(fragmentCode, ShaderType::Fragment);

		Initialize();
	}
	SpriteRenderer::SpriteRenderer(Shader* shader) : Renderer(shader)
	{
		Initialize();
	}
	void SpriteRenderer::Draw(const Texture& target, const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate)
	{
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

		m_Shader->SetUniform("coModel", model);
		m_Shader->SetUniform("coSpriteColor", color);

		glActiveTexture(GL_TEXTURE0);
		target.Bind();

		glBindVertexArray(m_QuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	void SpriteRenderer::Draw(const Texture& target, const glm::vec2& position)
	{
		Draw(target, position, target.GetImage().Size, Color::White, 0.f);
	}
	void SpriteRenderer::Initialize()
	{
		m_Shader->Bind().SetUniform("coImage", 0);

		int iViewport[4];
		glGetIntegerv(GL_VIEWPORT, iViewport);

		glm::mat4 projection = glm::ortho<float>(0.f, iViewport[2], iViewport[3], 0.f, -1.f, 1.f);
		m_Shader->SetUniform("coProjection", projection);

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
}