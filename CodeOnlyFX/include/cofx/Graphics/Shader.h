#pragma once

#include <string>
#include "Color.h"
#include <glm/mat4x4.hpp>

namespace co
{
	enum class ShaderType
	{
		Vertex,
		Fragment,
		Geometry
	};
	class Shader
	{
	private:
		uint32_t m_Shader;
	public:
		Shader();
		~Shader();

		void Attach(std::string_view shaderCode, ShaderType type);

		Shader& Bind();

		void SetUniform(std::string_view name, bool value) const;
		void SetUniform(std::string_view name, int value) const;
		void SetUniform(std::string_view name, float value) const;
		void SetUniform(std::string_view name, const Color& color) const;
		void SetUniform(std::string_view name, const glm::mat4& matrix) const;

		void Cleanup();
	private:
		static uint32_t CompileShader(std::string_view shaderCode, ShaderType type);
	};
}