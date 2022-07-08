#pragma once

#include "Vector.h"


namespace Athena
{
#define Size2 2

	template <typename Ty>
	class Vector<Ty, Size2>
	{
	public:
		using iterator = VectorIterator<Ty, Size2>;
		using const_iterator = VectorConstIterator<Ty, Size2>;

	public:
		Vector() = default;

		constexpr Vector(Ty value)
			: x(value), y(value) {}

		constexpr Vector(Ty X, Ty Y)
			: x(X), y(Y) {}

		template <typename U>
		constexpr Vector<Ty, Size2>(const Vector<U, Size2>& other)
		{
			static_assert(std::is_convertible<U, Ty>::value,
				"Vector initialization error: Vectors are not convertible");

			x = static_cast<Ty>(other.x);
			y = static_cast<Ty>(other.y);
		}

		template <typename U>
		constexpr Vector<Ty, Size2>& operator=(const Vector<U, Size2>& other)
		{
			static_assert(std::is_convertible<U, Ty>::value,
				"Vector assignment error: Vectors are not convertible");

			x = static_cast<Ty>(other.x);
			y = static_cast<Ty>(other.y);

			return *this;
		}

		template <typename U>
		constexpr Vector<Ty, Size2>(const Vector<U, 3>& other)
		{
			static_assert(std::is_convertible<U, Ty>::value,
				"Vector initialization error: Vectors are not convertible");

			x = static_cast<Ty>(other.x);
			y = static_cast<Ty>(other.y);
		}

		template <typename U>
		constexpr Vector<Ty, Size2>& operator=(const Vector<U, 3>& other)
		{
			static_assert(std::is_convertible<U, Ty>::value,
				"Vector assignment error: Vectors are not convertible");

			x = static_cast<Ty>(other.x);
			y = static_cast<Ty>(other.y);

			return *this;
		}

		template <typename U>
		constexpr Vector<Ty, Size2>(const Vector<U, 4>& other)
		{
			static_assert(std::is_convertible<U, Ty>::value,
				"Vector initialization error: Vectors are not convertible");

			x = static_cast<Ty>(other.x);
			y = static_cast<Ty>(other.y);
		}

		template <typename U>
		constexpr Vector<Ty, Size2>& operator=(const Vector<U, 4>& other)
		{
			static_assert(std::is_convertible<U, Ty>::value,
				"Vector assignment error: Vectors are not convertible");

			x = static_cast<Ty>(other.x);
			y = static_cast<Ty>(other.y);

			return *this;
		}

		constexpr void Fill(Ty value)
		{
			x = value;
			y = value;
		}

		constexpr const Ty& operator[](size_t idx) const
		{
			ATN_CORE_ASSERT(idx < Size2, "Vector subscript out of range");
			return *(&x + idx);
		}

		constexpr Ty& operator[](size_t idx)
		{
			ATN_CORE_ASSERT(idx < Size2, "Vector subscript out of range");
			return *(&x + idx);
		}

		constexpr size_t Size() const
		{
			return Size2;
		}

		constexpr Ty* Data() 
		{
			return &x;
		}

		constexpr const Ty* Data() const 
		{
			return &x;
		}

		constexpr iterator begin() 
		{
			return iterator(&x, 0);
		}

		constexpr iterator end() 
		{
			return iterator(&x, Size2);
		}

		constexpr const_iterator cbegin() const 
		{
			return const_iterator(&x, 0);
		}

		constexpr const_iterator cend() const 
		{
			return const_iterator(&x, Size2);
		}

		constexpr Vector& Apply(Ty (*func)(Ty))
		{
			x = func(x);
			y = func(y);
			return *this;
		}

		constexpr Ty SqrLength() const 
		{
			return x * x + y * y;
		}

		constexpr float Length() const 
		{
			return std::sqrt(static_cast<float>(SqrLength()));
		}

		constexpr Vector& Normalize()
		{
			float length = Length();
			return length == 0 ? *this : *this /= static_cast<Ty>(length);
		}

		constexpr Vector GetNormalized() const
		{
			float length = Length();
			return length == 0 ? Vector(*this) : Vector(*this) /= static_cast<Ty>(length);
		}

	public:
		constexpr Vector& operator+=(const Vector& other) 
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		constexpr Vector& operator-=(const Vector& other) 
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		constexpr Vector& operator+=(Ty scalar) 
		{
			x += scalar;
			y += scalar;
			return *this;
		}

		constexpr Vector& operator-=(Ty scalar) 
		{
			x -= scalar;
			y -= scalar;
			return *this;
		}

		constexpr Vector& operator*=(Ty scalar) 
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		constexpr Vector& operator/=(Ty scalar)
		{
			ATN_CORE_ASSERT(scalar != 0, "Vector operation error: dividing by zero");
			x /= scalar;
			y /= scalar;
			return *this;
		}

		constexpr Vector operator+(const Vector& other) const 
		{
			return Vector(x + other.x, y + other.y);
		}

		constexpr Vector operator-(const Vector& other) const 
		{
			return Vector(x - other.x, y - other.y);
		}

		constexpr Vector operator+(Ty scalar) const 
		{
			return Vector(x + scalar, y + scalar);
		}

		constexpr Vector operator-(Ty scalar) const 
		{
			return Vector(x - scalar, y - scalar);
		}

		constexpr Vector operator*(Ty scalar) const 
		{
			return Vector(x * scalar, y * scalar);
		}

		constexpr Vector operator/(Ty scalar) const
		{
			ATN_CORE_ASSERT(scalar != 0, "Vector operation error: dividing by zero");
			return Vector(x / scalar, y / scalar);
		}

		constexpr Vector operator-() const 
		{
			return Vector(-x, -y);
		}

		constexpr bool operator==(const Vector& other) const 
		{
			return x == other.x && y == other.y;
		}

		constexpr bool operator!=(const Vector& other) const 
		{
			return !(*this == other);
		}

	public:
		static const Vector<Ty, Size2> up;
		static const Vector<Ty, Size2> down;
		static const Vector<Ty, Size2> left;
		static const Vector<Ty, Size2> right;

	public:
		Ty x, y;
	};

	template<typename Ty>
	const Vector<Ty, Size2> Vector<Ty, Size2>::up = 
		Vector<Ty, Size2>(static_cast<Ty>(0), static_cast<Ty>(-1));

	template<typename Ty>
	const Vector<Ty, Size2> Vector<Ty, Size2>::down = 
		Vector<Ty, Size2>(static_cast<Ty>(0), static_cast<Ty>(1));

	template<typename Ty>
	const Vector<Ty, Size2> Vector<Ty, Size2>::left = 
		Vector<Ty, Size2>(static_cast<Ty>(-1), static_cast<Ty>(0));

	template<typename Ty>
	const Vector<Ty, Size2> Vector<Ty, Size2>::right = 
		Vector<Ty, Size2>(static_cast<Ty>(1), static_cast<Ty>(0));

#undef Size2
}
