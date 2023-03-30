#pragma once

#include "../System/Vector2.h"
#include <array>

namespace co
{
	class Transform
	{
	private:
		std::array<float, 16> m_Matrix;
	public:
		Transform();

		const std::array<float, 16>& GetMatrix() const;

		void Translate(const Vec2f& vec);
		void Scale(const Vec2f& scale);
		void Rotate(float rotate);
	};
}