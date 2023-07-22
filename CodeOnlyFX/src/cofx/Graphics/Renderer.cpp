#include "Graphics/Renderer.h"
#include "../glm/mat4x4.hpp"
#include "../glm/ext/matrix_transform.hpp"
#include "../glm/ext/matrix_clip_space.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Core/Debug.h"

namespace co
{
	Shader* Renderer::m_Shader = nullptr;
	uint32_t Renderer::m_QuadVAO = NULL;
	bool Renderer::m_Init = false;
	bool Renderer::m_Pair = false;

	Renderer::Renderer() { }

	void Renderer::Initialize()
	{
		const std::string vertexCode = R"(
#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}
)";
		const std::string fragmentCode = R"(
#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;
uniform bool useTex;

void main()
{
    if (useTex)
    {
        color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
        if (color.a == 0)
            discard;
    }
    else
        color = vec4(spriteColor, 1.0);
}  
)";
		m_Shader = new Shader();

		m_Shader->Attach(vertexCode, ShaderType::Vertex);
		m_Shader->Attach(fragmentCode, ShaderType::Fragment);

		m_Shader->Bind().SetUniform("image", 0);

		int iViewport[4];
		glGetIntegerv(GL_VIEWPORT, iViewport);

		glm::mat4 projection = glm::ortho<float>(0.f, iViewport[2], iViewport[3], 0.f, -1.f, 1.f);
		m_Shader->SetUniform("projection", projection);

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

		m_Init = true;
	}
	void Renderer::Begin()
	{
		if (!m_Init) Initialize();
		m_Pair = true;
	}
	void Renderer::Begin(Shader* shader)
	{
		if (!m_Init) Initialize();

		m_Shader = shader;

		m_Pair = true;
	}
	void Renderer::End()
	{
		m_Pair = false;
	}
	void Renderer::DrawRect(const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate)
	{
		if (!m_Pair)
		{
			Debug::Warn("cofx::Graphics::Renderer; Renderer::DrawRect must be between Renderer::Begin and Renderer::End pairs.");
			return;
		}
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
	void Renderer::Draw(const Texture& target, const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate)
	{
		if (!m_Pair)
		{
			Debug::Warn("cofx::Graphics::Renderer; Renderer::Draw must be between Renderer::Begin and Renderer::End pairs.");
			return;
		}
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
		target.Bind();

		glBindVertexArray(m_QuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	void Renderer::DrawString()
	{
		if (!m_Pair)
		{
			Debug::Warn("cofx::Graphics::Renderer; Renderer::DrawString must be between Renderer::Begin and Renderer::End pairs.");
			return;
		}
	}
}