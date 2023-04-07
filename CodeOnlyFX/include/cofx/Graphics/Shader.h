#pragma once

#include <string>
#include "Color.h"
#include "Matrix.h"

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
		unsigned int m_Shader;
	public:
		Shader();
		~Shader();

		void Attach(std::string_view shaderCode, ShaderType type);

		unsigned int GetRawShader() const;
		Shader& Bind();

		void SetUniform(std::string_view name, bool value) const;
		void SetUniform(std::string_view name, int value) const;
		void SetUniform(std::string_view name, float value) const;
		void SetUniform(std::string_view name, const Color& color) const;
		void SetUniform(std::string_view name, const Matrix& matrix) const;

		void Cleanup();
	private:
		static unsigned int CompileShader(std::string_view shaderCode, ShaderType type);
	};
}