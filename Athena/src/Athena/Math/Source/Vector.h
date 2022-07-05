#pragma once

#include "Athena/Core/Core.h"


namespace Athena
{
	template <typename Ty, size_t Size>
	class VectorConstIterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = ptrdiff_t;
		using pointer = const Ty*;
		using reference = const Ty&;

	public:
		constexpr VectorConstIterator()
			: m_Ptr(nullptr), m_Idx(0) {}

		constexpr explicit VectorConstIterator(pointer Ptr, size_t Off = 0)
			: m_Ptr(Ptr), m_Idx(Off) {}

		constexpr reference operator*() const
		{
			return *operator->();
		}

		constexpr pointer operator->() const
		{
			ATN_CORE_ASSERT(m_Ptr, "Cannot dereference value-initialized vector iterator");
			ATN_CORE_ASSERT(m_Idx < Size, "Cannot dereference out of range vector iterator");
			return m_Ptr + m_Idx;
		}

		constexpr VectorConstIterator& operator++()
		{
			ATN_CORE_ASSERT(m_Ptr, "Cannot increment value-initialized vector iterator");
			ATN_CORE_ASSERT(m_Idx < Size, "Cannot increment vector iterator past end");
			++m_Idx;
			return *this;
		}

		constexpr VectorConstIterator operator++(int)
		{
			VectorConstIterator tmp = *this;
			++* this;
			return tmp;
		}

		constexpr VectorConstIterator& operator--()
		{
			ATN_CORE_ASSERT(m_Ptr, "Cannot decrement value-initialized array iterator");
			ATN_CORE_ASSERT(m_Idx != 0, "Cannot decrement vector iterator before begin");
			--m_Idx;
			return *this;
		}

		constexpr VectorConstIterator operator--(int)
		{
			VectorConstIterator tmp = *this;
			--*this;
			return tmp;
		}

		constexpr VectorConstIterator& operator+=(const ptrdiff_t Off)
		{
			VerifyOffset(Off);
			m_Idx += static_cast<size_t>(Off);
			return *this;
		}

		constexpr VectorConstIterator operator+(const ptrdiff_t Off) const
		{
			VectorConstIterator tmp = *this;
			return tmp += Off;
		}

		constexpr VectorConstIterator& operator-=(const ptrdiff_t Off)
		{
			return *this += -Off;
		}

		constexpr VectorConstIterator operator-(const ptrdiff_t Off) const
		{
			VectorConstIterator tmp = *this;
			return tmp -= Off;
		}

		constexpr ptrdiff_t operator-(const VectorConstIterator& other) const
		{
			Compat(other);
			return static_cast<ptrdiff_t>(m_Idx - other.m_Idx);
		}

		constexpr reference operator[](const ptrdiff_t Off) const
		{
			return *(*this + Off);
		}

		constexpr bool operator==(const VectorConstIterator& other) const
		{
			Compat(other);
			return m_Idx == other.m_Idx;
		}

		constexpr bool operator!=(const VectorConstIterator& other) const
		{
			return !(*this == other);
		}

		constexpr bool operator<(const VectorConstIterator& other) const
		{
			Compat(other);
			return m_Idx < other.m_Idx;
		}

		constexpr bool operator>(const VectorConstIterator& other) const
		{
			return other < *this;
		}

		constexpr bool operator<=(const VectorConstIterator& other) const
		{
			return !(other < *this);
		}

		constexpr bool operator>=(const VectorConstIterator& other) const
		{
			return !(*this < other);
		}

	private:
		constexpr void Compat(const VectorConstIterator& other) const
		{
			ATN_CORE_ASSERT(m_Ptr == other.m_Ptr, "Vector iterators incompatible");
		}

		constexpr void VerifyOffset(const ptrdiff_t Off) const
		{
			if (Off != 0)
				ATN_CORE_ASSERT(m_Ptr, "Cannot seek value-initialized vector iterator");

			if (Off < 0)
				ATN_CORE_ASSERT(m_Idx >= size_t{ 0 } - static_cast<size_t>(Off), "Cannot seek vector iterator before begin");

			if (Off > 0)
				ATN_CORE_ASSERT(Size - m_Idx >= static_cast<size_t>(Off), "Cannot seek vector iterator after end");
		}

	private:
		pointer m_Ptr;
		size_t m_Idx;
	};


	template <class Ty, size_t Size>
	constexpr VectorConstIterator<Ty, Size> operator+(
		const ptrdiff_t Off, VectorConstIterator<Ty, Size> Iter)
	{
		return Iter += Off;
	}


	template <class Ty, size_t Size>
	class VectorIterator: public VectorConstIterator<Ty, Size>
	{
	public:
		using Base = VectorConstIterator<Ty, Size>;

		using iterator_category = std::random_access_iterator_tag;
		using difference_type = ptrdiff_t;
		using pointer = Ty*;
		using reference = Ty&;

	public:
		constexpr VectorIterator() = default;

		constexpr explicit VectorIterator(pointer Ptr, size_t Off = 0)
			: Base(Ptr, Off) {}

		constexpr reference operator*() const
		{
			return const_cast<reference>(Base::operator*());
		}

		constexpr pointer operator->() const
		{
			return const_cast<pointer>(Base::operator->());
		}

		constexpr VectorIterator& operator++()
		{
			Base::operator++();
			return *this;
		}

		constexpr VectorIterator operator++(int)
		{
			VectorIterator tmp = *this;
			Base::operator++();
			return tmp;
		}

		constexpr VectorIterator& operator--()
		{
			Base::operator--();
			return *this;
		}

		constexpr VectorIterator operator--(int)
		{
			VectorIterator tmp = *this;
			Base::operator--();
			return tmp;
		}

		constexpr VectorIterator& operator+=(const ptrdiff_t Off)
		{
			Base::operator+=(Off);
			return *this;
		}

		constexpr VectorIterator operator+(const ptrdiff_t Off) const
		{
			VectorIterator tmp = *this;
			return tmp += Off;
		}

		constexpr VectorIterator& operator-=(const ptrdiff_t Off)
		{
			Base::operator-=(Off);
			return *this;
		}

		using Base::operator-;

		constexpr VectorIterator operator-(const ptrdiff_t Off) const
		{
			VectorIterator tmp = *this;
			return tmp -= Off;
		}

		constexpr reference operator[](const ptrdiff_t Off) const
		{
			return const_cast<reference>(Base::operator[](Off));
		}
	};

	template <class Ty, size_t Size>
	constexpr VectorIterator<Ty, Size> operator+(
		const ptrdiff_t Off, VectorIterator<Ty, Size> Next)
	{
		return Next += Off;
	}


	template <typename Ty, size_t _Size>
	class Vector
	{
	public:
		using iterator = VectorIterator<Ty, _Size>;
		using const_iterator = VectorConstIterator<Ty, _Size>;

	public:
		Vector() = default;

		constexpr Vector(Ty value)
		{
			Fill(value);
		}

		constexpr Vector(const std::initializer_list<Ty>& values)
		{
			ATN_CORE_ASSERT(values.size() == _Size,
				"Cannot initialize vector with initializer list");

			size_t iter = 0;
			for (auto val : values)
			{
				m_Array[iter] = val;
				++iter;
			}
		}

		constexpr Vector(const Vector& other) = default;

		template <typename U>
		constexpr Vector<Ty, _Size>(const Vector<U, _Size>& other)
		{
			static_assert(std::is_convertible<U, Ty>::value,
				"Vector initialization error: Vectors are not convertible");

			for (size_t i = 0; i < _Size; ++i)
				m_Array[i] = static_cast<Ty>(other[i]);
		}

		constexpr Vector& operator=(const Vector& other) = default;

		template <typename U>
		constexpr Vector<Ty, _Size>& operator=(const Vector<U, _Size>& other)
		{
			static_assert(std::is_convertible<U, Ty>::value,
				"Vector assignment error: Vectors are not convertible");

			for (size_t i = 0; i < _Size; ++i)
				m_Array[i] = static_cast<Ty>(other[i]);

			return *this;
		}

		constexpr void Fill(Ty value)
		{
			for (size_t i = 0; i < _Size; ++i)
				m_Array[i] = value;
		}

		constexpr const Ty& operator[](size_t idx) const
		{
			ATN_CORE_ASSERT(idx < _Size, "Vector subscript out of range");
			return m_Array[idx];
		}

		constexpr Ty& operator[](size_t idx)
		{
			ATN_CORE_ASSERT(idx < _Size, "Vector subscript out of range");
			return m_Array[idx];
		}

		constexpr size_t Size() const 
		{
			return _Size;
		}

		constexpr Ty* Data() 
		{
			return m_Array;
		}

		constexpr const Ty* Data() const 
		{
			return m_Array;
		}

		constexpr iterator begin() 
		{
			return iterator(m_Array, 0);
		}

		constexpr iterator end() 
		{
			return iterator(m_Array, _Size);
		}

		constexpr const_iterator cbegin() const 
		{
			return const_iterator(m_Array, 0);
		}

		constexpr const_iterator cend() const 
		{
			return const_iterator(m_Array, _Size);
		}

		constexpr Vector& Apply(Ty (*func)(Ty))
		{
			for (size_t i = 0; i < _Size; ++i)
				m_Array[i] = func(m_Array[i]);
			return *this;
		}

		constexpr Ty SqrLength() const 
		{
			Ty out;
			for (size_t i = 0; i < _Size; ++i)
				out += m_Array[i] * m_Array[i];
			return out;
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
			for (size_t i = 0; i < _Size; ++i)
				m_Array[i] += other.m_Array[i];
			return *this;
		}

		constexpr Vector& operator-=(const Vector& other) 
		{
			for (size_t i = 0; i < _Size; ++i)
				m_Array[i] -= other.m_Array[i];
			return *this;
		}

		constexpr Vector& operator+=(Ty scalar) 
		{
			for (size_t i = 0; i < _Size; ++i)
				m_Array[i] += scalar;
			return *this;
		}

		constexpr Vector& operator-=(Ty scalar) 
		{
			for (size_t i = 0; i < _Size; ++i)
				m_Array[i] -= scalar;
			return *this;
		}

		constexpr Vector& operator*=(Ty scalar) 
		{
			for (size_t i = 0; i < _Size; ++i)
				m_Array[i] *= scalar;
			return *this;
		}

		constexpr Vector& operator/=(Ty scalar)
		{
			ATN_CORE_ASSERT(scalar != 0, "Vector operation error: dividing by zero");
			for (size_t i = 0; i < _Size; ++i)
				m_Array[i] /= scalar;
			return *this;
		}

		constexpr Vector operator+(const Vector& other) const 
		{
			return Vector(*this) += other;
		}

		constexpr Vector operator-(const Vector& other) const 
		{
			return Vector(*this) -= other;
		}

		constexpr Vector operator+(Ty scalar) const 
		{
			return Vector(*this) += scalar;
		}

		constexpr Vector operator-(Ty scalar) const 
		{
			return Vector(*this) -= scalar;
		}

		constexpr Vector operator*(Ty scalar) const 
		{
			return Vector(*this) *= scalar;
		}

		constexpr Vector operator/(Ty scalar) const
		{
			ATN_CORE_ASSERT(scalar != 0, "Vector operation error: dividing by zero");
			return Vector(*this) /= scalar;
		}

		constexpr Vector operator-() const 
		{
			Vector out(*this);
			for (size_t i = 0; i < _Size; ++i)
				out.m_Array[i] = -out.m_Array[i];
			return out;
		}

		constexpr bool operator==(const Vector& other) const 
		{
			bool out = true;
			for (size_t i = 0; i < _Size; ++i)
				out = out && m_Array[i] == other.m_Array[i];
			return out;
		}

		constexpr bool operator!=(const Vector& other) const 
		{
			return !(*this == other);
		}

	private:
		Ty m_Array[_Size];
	};
}
