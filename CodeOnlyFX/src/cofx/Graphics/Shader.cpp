#include "Graphics/Shader.h"
#include "Core/Debug.h"
#include <GL/glew.h>

namespace co
{
	Shader::Shader() : m_Shader(NULL), m_VertexAttached(false), m_FragmentAttached(false), m_GeometryAttached(false)
	{
	}
	Shader::~Shader()
	{
		Cleanup();
	}
	void Shader::Attach(std::string_view shaderCode, ShaderType type)
	{
		uint32_t shader = CompileShader(shaderCode, type);
		int success = 0;
		char infoLog[512]{};

		if (m_Shader == NULL)
			m_Shader = glCreateProgram();
		glAttachShader(m_Shader, shader);
		glLinkProgram(m_Shader);
		glGetProgramiv(m_Shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_Shader, 512, NULL, infoLog);
			CO_CRITICAL("cofx::Graphics::Shader; Failed to link shader program : {}", infoLog);
			return;
		}

		glDeleteShader(shader);

		switch (type)
		{
		case ShaderType::Vertex:
			m_VertexAttached = true;
			break;
		case ShaderType::Fragment:
			m_FragmentAttached = true;
			break;
		case ShaderType::Geometry:
			m_GeometryAttached = true;
			break;
		}
	}
	void Shader::FillDefaultShaders()
	{
		if (!m_VertexAttached)
		{
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
			Attach(vertexCode, ShaderType::Vertex);
		}
		if (!m_FragmentAttached)
		{
			const std::string fragmentCode = R"(
#version 330 core
in vec2 coTexCoords;
out vec4 coColor;

uniform sampler2D coImage;
uniform vec3 coSpriteColor;
uniform bool coUseTex;

void main()
{
    if (coUseTex)
    {
        coColor = vec4(coSpriteColor, 1.0) * texture(coImage, coTexCoords);
        if (coColor.a == 0)
            discard;
    }
    else
        coColor = vec4(coSpriteColor, 1.0);
}  
)";
			Attach(fragmentCode, ShaderType::Fragment);
		}
	}
	Shader& Shader::Bind()
	{
		glUseProgram(m_Shader);
		return *this;
	}
	void Shader::SetUniform(std::string_view name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_Shader, name.data()), static_cast<int>(value));
	}
	void Shader::SetUniform(std::string_view name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_Shader, name.data()), value);
	}
	void Shader::SetUniform(std::string_view name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_Shader, name.data()), value);
	}
	void Shader::SetUniform(std::string_view name, const Color& color) const
	{
		glUniform3f(glGetUniformLocation(m_Shader, name.data()), static_cast<float>(color.R / 255.f), static_cast<float>(color.G / 255.f), static_cast<float>(color.B / 255.f));
	}
	void Shader::SetUniform(std::string_view name, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_Shader, name.data()), 1, false, &matrix[0][0]);
	}
	void Shader::Cleanup()
	{
		if (m_Shader)
			glDeleteProgram(m_Shader);
	}
	uint32_t Shader::CompileShader(std::string_view shaderCode, ShaderType type)
	{
		auto cShaderCode = shaderCode.data();

		int success = 0;
		char infoLog[512]{};

		uint32_t shader = NULL;

		if (type == ShaderType::Vertex)
		{
			shader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(shader, 1, &cShaderCode, nullptr);
			glCompileShader(shader);

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				CO_CRITICAL("cofx::Graphics::Shader; Failed to compile vertex shader. {}", infoLog);
				return NULL;
			}
		}
		else
		{
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(shader, 1, &cShaderCode, nullptr);
			glCompileShader(shader);

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				CO_CRITICAL("cofx::Graphics::Shader; Failed to compile fragment shader. {}", infoLog);
				return NULL;
			}
		}
		return shader;
	}
}