#include "Graphics/Renderer.h"
#include "../glm/mat4x4.hpp"
#include "../glm/ext/matrix_transform.hpp"
#include "../glm/ext/matrix_clip_space.hpp"
#include <GL/glew.h>

namespace co
{
	Renderer::Renderer(const glm::uvec2& windowSize) : m_QuadVAO(NULL)
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
		m_Shader.Attach(vertexCode, ShaderType::Vertex);
		m_Shader.Attach(fragmentCode, ShaderType::Fragment);

		m_Shader.Bind().SetUniform("image", 0);

		glm::mat4 projection = glm::ortho<float>(0.f, windowSize.x, windowSize.y, 0.f, -1.f, 1.f);
		m_Shader.SetUniform("projection", projection);

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
	void Renderer::Draw(const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate)
	{
		m_Shader.Bind().SetUniform("useTex", false);
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

		m_Shader.SetUniform("model", model);
		m_Shader.SetUniform("spriteColor", color);

		glBindVertexArray(m_QuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	void Renderer::Draw(Texture& texture, const glm::vec2& position, const glm::vec2& size, const Color& color, float rotate)
	{
		m_Shader.Bind().SetUniform("useTex", true);
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

		m_Shader.SetUniform("model", model);
		m_Shader.SetUniform("spriteColor", color);

		glActiveTexture(GL_TEXTURE0);
		texture.Bind();

		glBindVertexArray(m_QuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
}