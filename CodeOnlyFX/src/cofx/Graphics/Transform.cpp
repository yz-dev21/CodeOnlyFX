#include "Graphics/Transform.h"
#include <algorithm>

namespace co
{
	Transform::Transform()
	{
		m_Matrix =
		{
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		};
	}
	const std::array<float, 16>& Transform::GetMatrix() const
	{
		return m_Matrix;
	}
	void Transform::Translate(const Vec2f& vec)
	{
		for (size_t i = 0; i < 4; i++)
		{
			m_Matrix[i + 4 * 3] = (m_Matrix[i] * vec.X
				+ m_Matrix[i + 4 * 1] * vec.Y
				+ m_Matrix[i + 4 * 2] * 0
				+ m_Matrix[i + 4 * 3]);
		}
	}
	void Transform::Scale(const Vec2f& scale)
	{
		for (size_t i = 0; i < 4; i++)
		{
			m_Matrix[i] *= scale.X;
			m_Matrix[i + 4 * 1] *= scale.Y;
			m_Matrix[i + 4 * 2] *= 1;
		}
	}
	void Transform::Rotate(float angle)
	{
		float rad = angle * (3.14159265359f / 180.f);
		float cos = std::cos(rad);
		float sin = std::cos(rad);
	}
}