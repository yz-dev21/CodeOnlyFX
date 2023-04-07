#pragma once

#include "System/Vector2.h"
#include <array>

namespace co
{
	class Matrix
	{
	private:
		std::array<float, 16> m_Array;
	public:
		Matrix();
		Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31,
			float m32, float m33, float m34, float m41, float m42, float m43, float m44);

		float& operator[](int index);

		void Combine(const Matrix& mat);

		void Translate(const Vec2f& vec);
		void Scale(const Vec2f& size);
		void Rotate(float angle);
		void LookAt();
		void Orthographic(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);

		const std::array<float, 16>& GetRawMatrix() const;
	};
}