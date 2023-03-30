#include <cmath>

namespace co
{
	template <typename T>
	Vector2<T>::Vector2() { }
	template <typename T>
	Vector2<T>::Vector2(T x, T y) : X(x), Y(y)
	{
	}
	template <typename T>
	Vector2<T>::Vector2(const Vector2& copy) : X(copy.X), Y(copy.Y)
	{
	}
	template <typename T>
	T Vector2<T>::Length() const
	{
		return std::sqrt(X * X + Y * Y);
	}
	template <typename T>
	T Vector2<T>::LengthSquared() const
	{
		return X * X + Y * Y;
	}
	template <typename T>
	Vector2<T> Vector2<T>::Normalized() const
	{
		return (*this) / Length();
	}
	template <typename T>
	float Vector2<T>::Dot(const Vector2& vec)
	{
		return X * vec.X + Y * vec.Y;
	}
	template <typename T>
	const Vector2<T> Vector2<T>::Zero = Vector2(0, 0);
	template <typename T>
	Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2(left.X + right.X, left.Y + right.Y);
	}
	template <typename T>
	Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right)
	{
		left.X += right.X;
		left.Y += right.Y;

		return left;
	}
	template <typename T>
	Vector2<T> operator-(const Vector2<T>& vec)
	{
		return Vector2(-vec.X, -vec.Y);
	}
	template <typename T>
	Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2(left.X - right.X, left.Y - right.Y);
	}
	template <typename T>
	Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right)
	{
		left.X -= right.X;
		left.Y -= right.Y;

		return left;
	}
	template <typename T>
	Vector2<T> operator*(const Vector2<T>& left, T scale)
	{
		return Vector2(left.X * scale, left.Y * scale);
	}
	template <typename T>
	Vector2<T> operator*(T scale, const Vector2<T>& right)
	{
		return Vector2(right.X * scale, right.Y * scale);
	}
	template <typename T>
	Vector2<T>& operator*=(Vector2<T>& left, T scale)
	{
		left.X *= scale;
		left.Y *= scale;

		return left;
	}
	template <typename T>
	Vector2<T> operator/(const Vector2<T>& left, T scale)
	{
		return Vector2(left.X / scale, left.Y / scale);
	}
	template <typename T>
	Vector2<T>& operator/=(Vector2<T>& left, T scale)
	{
		left.X /= scale;
		left.Y /= scale;

		return left;
	}
	template <typename T>
	bool operator==(const Vector2<T>& left, const Vector2<T>& right)
	{
		return (left.X == right.X) & (left.Y == right.Y);
	}
	template <typename T>
	bool operator!=(const Vector2<T>& left, const Vector2<T>& right)
	{
		return (left.X != right.X) || (left.Y != right.Y);
	}
}