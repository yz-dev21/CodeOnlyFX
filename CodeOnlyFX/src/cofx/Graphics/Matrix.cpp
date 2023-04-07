#include "Graphics/Matrix.h"

namespace co
{
	Matrix::Matrix()
	{
		m_Array = {
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		};
	}
	float& Matrix::operator[](int index)
	{
		return m_Array[index];
	}
	void Matrix::Combine(const Matrix& mat)
	{
		m_Array[0] = m_Array[0] * mat.m_Array[0] + m_Array[1] * mat.m_Array[4] + m_Array[2] * mat.m_Array[8] + m_Array[3] * mat.m_Array[12];
		m_Array[1] = m_Array[0] * mat.m_Array[1] + m_Array[1] * mat.m_Array[5] + m_Array[2] * mat.m_Array[9] + m_Array[3] * mat.m_Array[13];
		m_Array[2] = m_Array[0] * mat.m_Array[2] + m_Array[1] * mat.m_Array[6] + m_Array[2] * mat.m_Array[10] + m_Array[3] * mat.m_Array[14];
		m_Array[3] = m_Array[0] * mat.m_Array[3] + m_Array[1] * mat.m_Array[7] + m_Array[2] * mat.m_Array[11] + m_Array[3] * mat.m_Array[15];
		m_Array[4] = m_Array[4] * mat.m_Array[0] + m_Array[5] * mat.m_Array[4] + m_Array[6] * mat.m_Array[8] + m_Array[7] * mat.m_Array[12];
		m_Array[5] = m_Array[4] * mat.m_Array[1] + m_Array[5] * mat.m_Array[5] + m_Array[6] * mat.m_Array[9] + m_Array[7] * mat.m_Array[13];
		m_Array[6] = m_Array[4] * mat.m_Array[2] + m_Array[5] * mat.m_Array[6] + m_Array[6] * mat.m_Array[10] + m_Array[7] * mat.m_Array[14];
		m_Array[7] = m_Array[4] * mat.m_Array[3] + m_Array[5] * mat.m_Array[7] + m_Array[6] * mat.m_Array[11] + m_Array[7] * mat.m_Array[15];
		m_Array[8] = m_Array[8] * mat.m_Array[0] + m_Array[9] * mat.m_Array[4] + m_Array[10] * mat.m_Array[8] + m_Array[11] * mat.m_Array[12];
		m_Array[9] = m_Array[8] * mat.m_Array[1] + m_Array[9] * mat.m_Array[5] + m_Array[10] * mat.m_Array[9] + m_Array[11] * mat.m_Array[13];
		m_Array[10] = m_Array[8] * mat.m_Array[2] + m_Array[9] * mat.m_Array[6] + m_Array[10] * mat.m_Array[10] + m_Array[11] * mat.m_Array[14];
		m_Array[11] = m_Array[8] * mat.m_Array[3] + m_Array[9] * mat.m_Array[7] + m_Array[10] * mat.m_Array[11] + m_Array[11] * mat.m_Array[15];
		m_Array[12] = m_Array[12] * mat.m_Array[0] + m_Array[13] * mat.m_Array[4] + m_Array[14] * mat.m_Array[8] + m_Array[15] * mat.m_Array[12];
		m_Array[13] = m_Array[12] * mat.m_Array[1] + m_Array[13] * mat.m_Array[5] + m_Array[14] * mat.m_Array[9] + m_Array[15] * mat.m_Array[13];
		m_Array[14] = m_Array[12] * mat.m_Array[2] + m_Array[13] * mat.m_Array[6] + m_Array[14] * mat.m_Array[10] + m_Array[15] * mat.m_Array[14];
		m_Array[15] = m_Array[12] * mat.m_Array[3] + m_Array[13] * mat.m_Array[7] + m_Array[14] * mat.m_Array[11] + m_Array[15] * mat.m_Array[15];
	}
	void Matrix::Translate(const Vec2f& vec)
	{
		Matrix mat;
		mat.m_Array[12] = vec.X;
		mat.m_Array[13] = vec.Y;

		Combine(mat);
	}
	void Matrix::Scale(const Vec2f& size)
	{
		Matrix mat;
		mat.m_Array[0] = size.X;
		mat.m_Array[5] = size.Y;

		Combine(mat);
	}
	void Matrix::Rotate(float angle)
	{
		float rad = angle * (3.14159265359f / 180.f);
		float cos = std::cos(rad);
		float sin = std::sin(rad);

		Matrix mat;
		mat.m_Array[5] = cos;
		mat.m_Array[6] = sin;
		mat.m_Array[9] = -sin;
		mat.m_Array[10] = cos;

		Combine(mat);
	}
	void Matrix::Orthographic(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
	{
		Matrix mat;
		mat.m_Array[0] = 2.f / (right - left);
		mat.m_Array[1] = 0.f;
		mat.m_Array[2] = 0.f;
		mat.m_Array[3] = 0.f;
		mat.m_Array[4] = 0.f;
		mat.m_Array[5] = 2.f / (top - bottom);
		mat.m_Array[6] = 0.f;
		mat.m_Array[7] = 0.f;
		mat.m_Array[8] = 0.f;
		mat.m_Array[9] = 0.f;
		mat.m_Array[10] = 1.f / (zNearPlane - zFarPlane);
		mat.m_Array[11] = 0.f;
		mat.m_Array[12] = (left + right) / (left - right);
		mat.m_Array[13] = (top + bottom) / (bottom - top);
		mat.m_Array[14] = zNearPlane / (zNearPlane - zFarPlane);
		mat.m_Array[15] = 1.f;

		Combine(mat);
	}
	const std::array<float, 16>& Matrix::GetRawMatrix() const
	{
		return m_Array;
	}
}