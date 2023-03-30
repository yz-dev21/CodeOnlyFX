#pragma once

namespace co
{
	template <typename T>
	struct Vector2
	{
		T X{}, Y{};

		Vector2();
		Vector2(T x, T y);
		Vector2(const Vector2& copy);

		T Length() const;
		T LengthSquared() const;
		Vector2 Normalized() const;
		float Dot(const Vector2& vec);

		static const Vector2<T> Zero;
	};
	using Vec2f = Vector2<float>;
	using Vec2i = Vector2<int>;
	using Vec2u = Vector2<unsigned int>;

	template <typename T>
	Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right);
	template <typename T>
	Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T> operator-(const Vector2<T>& vec);
	template <typename T>
	Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right);
	template <typename T>
	Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T> operator*(const Vector2<T>& left, T scale);
	template <typename T>
	Vector2<T> operator*(T scale, const Vector2<T>& right);
	template <typename T>
	Vector2<T>& operator*=(Vector2<T>& left, T scale);

	template <typename T>
	Vector2<T> operator/(const Vector2<T>& left, T scale);
	template <typename T>
	Vector2<T>& operator/=(Vector2<T>& left, T scale);

	template <typename T>
	bool operator==(const Vector2<T>& left, const Vector2<T>& right);
	template <typename T>
	bool operator!=(const Vector2<T>& left, const Vector2<T>& right);
}
#include "Vector2.inl"