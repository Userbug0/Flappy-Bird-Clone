#pragma once

#include "Athena/Core/Core.h"
#include "Athena/Math/Vector.h"


namespace Athena
{
	// ROW-MAJOR
	template <typename Ty, size_t Column, size_t Row>
	class Matrix
	{
	private:
		using vRow = Vector<Ty, Row>;
		using vColumn = Vector<Ty, Column>;

	public:
		using iterator = VectorIterator<Vector<Ty, Row>, Column>;
		using const_iterator = VectorConstIterator<Vector<Ty, Row>, Column>;

	public:
		constexpr Matrix() = default;

		constexpr Matrix(Ty value)
		{
			for (size_t i = 0; i < Column; ++i)
				m_Array[i].Fill(value);
		}

		constexpr Matrix(const std::initializer_list<vRow>& values)
		{
			ATN_CORE_ASSERT(values.size() == Column, 
				"Cannot initialize matrix with initializer list");
			size_t idx = 0;
			for (auto& row : values)
			{
				m_Array[idx] = row;
				++idx;
			}
		}

		constexpr Matrix(const vRow& vec)
		{
			static_assert(Column == 1, "Cannot initialize matrix with vector");
			m_Array[0] = vec;
		}

		constexpr explicit operator Vector<Ty, Row>() const
		{
			static_assert(Column == 1, "Cannot convert matrix to vector");
			return m_Array[0];
		}

		template <typename U>
		constexpr Matrix(const Vector<U, Row>& vec)
		{
			static_assert(std::is_convertible<U, Ty>::value, 
				"Matrix and vector are not convertible");
			static_assert(Column == 1, "Cannot initialize matrix with vector");
			m_Array[0] = vec;
		}

		constexpr Matrix(const Matrix& other) = default;

		template <typename U>
		constexpr Matrix(const Matrix<U, Column, Row>& other)
		{
			static_assert(std::is_convertible<U, Ty>::value,
				"Matrix and vector are not convertible");
			for (size_t i = 0; i < Column; ++i)
			{
				for (size_t j = 0; j < Row; ++j)
					m_Array[i][j] = static_cast<Ty>(other[i][j]);
			}
		}

		constexpr Matrix& operator=(const Matrix& other) = default;

		template <typename U>
		constexpr Matrix<Ty, Column, Row>& operator=(const Matrix<U, Column, Row>& other)
		{
			static_assert(std::is_convertible<U, Ty>::value,
				"Matrix and vector are not convertible");
			for (size_t i = 0; i < Column; ++i)
			{
				for (size_t j = 0; j < Row; ++j)
					m_Array[i][j] = static_cast<Ty>(other[i][j]);
			}
		}

		static constexpr Matrix<Ty, Column, Row> Identity()
		{
			Matrix out(static_cast<Ty>(0));

			constexpr size_t min = min(Column, Row);
			for (size_t i = 0; i < min; ++i)
				out[i][i] = static_cast<Ty>(1);

			return out;
		}

		constexpr Ty* Data()
		{
			return &m_Array[0][0];
		}

		constexpr const Ty* Data() const
		{
			return &m_Array[0][0];
		}

		constexpr vColumn GetColumn(size_t idx) const
		{
			ATN_CORE_ASSERT(idx < Row, "Matrix subscript out of range");
			vColumn out;
			for (size_t i = 0; i < Column; ++i)
				out[i] = m_Array[i][idx];
			return out;
		}

		constexpr size_t SizeOfRow() const
		{
			return Row;
		}

		constexpr size_t SizeOfColumn() const
		{
			return Column;
		}

		constexpr iterator begin()
		{
			return iterator(m_Array, 0);
		}

		constexpr iterator end()
		{
			return iterator(m_Array, Column);
		}

		constexpr const_iterator cbegin() const
		{
			return const_iterator(m_Array, 0);
		}

		constexpr const_iterator cend() const
		{
			return const_iterator(m_Array, Column);
		}

		constexpr const vRow& operator[](size_t idx) const
		{
			ATN_CORE_ASSERT(idx < Column, "Matrix subscript out of range");
			return m_Array[idx];
		}

		constexpr vRow& operator[](size_t idx)
		{
			ATN_CORE_ASSERT(idx < Column, "Matrix subscript out of range");
			return m_Array[idx];
		}
		
		constexpr Matrix& Apply(Ty(*func)(Ty))
		{
			for (size_t i = 0; i < Column; ++i)
				m_Array[i].Apply(func);
			return *this;
		}

		constexpr Matrix& Fill(Ty value)
		{
			for (size_t i = 0; i < Column; ++i)
				m_Array[i].Fill(value);
			return *this;
		}

	public:
		constexpr Matrix& operator+=(const Matrix& other)
		{
			for (size_t i = 0; i < Column; ++i)
				m_Array[i] += other[i];
			return *this;
		}

		constexpr Matrix& operator-=(const Matrix& other)
		{
			for (size_t i = 0; i < Column; ++i)
				m_Array[i] -= other[i];
			return *this;
		}

		constexpr Matrix& operator+=(float scalar)
		{
			for (size_t i = 0; i < Column; ++i)
				m_Array[i] += scalar;
			return *this;
		}

		constexpr Matrix& operator-=(float scalar)
		{
			for (size_t i = 0; i < Column; ++i)
				m_Array[i] -= scalar;
			return *this;
		}

		constexpr Matrix& operator*=(float scalar)
		{
			for (size_t i = 0; i < Column; ++i)
				m_Array[i] *= scalar;
			return *this;
		}

		constexpr Matrix& operator/=(float scalar)
		{
			ATN_CORE_ASSERT(scalar != 0, "Matrix operation error: dividing by zero");
			for (size_t i = 0; i < Column; ++i)
				for (size_t j = 0; j < Row; ++j)
					m_Array[i][j] /= scalar;
			return *this;
		}

		constexpr Matrix operator+(const Matrix& other) const
		{
			return Matrix(*this) += other;
		}

		constexpr Matrix operator-(const Matrix& other) const
		{
			return Matrix(*this) -= other;
		}

		template <size_t OtherColumn, size_t OtherRow>
		constexpr Matrix<Ty, Column, OtherRow> operator*(const Matrix<Ty, OtherColumn, OtherRow>& other) const
		{
			static_assert(Row == OtherColumn, "Invalid Matrix multiplication");

			Matrix<Ty, Column, OtherRow> out(static_cast<Ty>(0));
			for (size_t i = 0; i < Column; i++)
			{
				for (size_t j = 0; j < OtherRow; j++)
				{
					for (size_t k = 0; k < Row; ++k)
						out[i][j] += m_Array[i][k] * other[k][j];
				}
			}
			return out;
		}

		constexpr Matrix operator+(float scalar) const
		{
			return Matrix(*this) += scalar;
		}

		constexpr Matrix operator-(float scalar) const
		{
			return Matrix(*this) -= scalar;
		}

		constexpr Matrix operator*(float scalar) const
		{
			return Matrix(*this) *= scalar;
		}

		constexpr Matrix operator/(float scalar) const
		{
			return Matrix(*this) /= scalar;
		}

	private:
		vRow m_Array[Column];
	};
}
