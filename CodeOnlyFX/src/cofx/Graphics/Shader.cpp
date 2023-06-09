#include "Graphics/Shader.h"
#include "Core/Debug.h"
#include <GL/glew.h>

namespace co
{
	Shader::Shader() : m_Shader(NULL)
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
	}
	uint32_t Shader::GetRawShader() const
	{
		return m_Shader;
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