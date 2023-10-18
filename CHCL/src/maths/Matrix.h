#pragma once

#include <functional>

namespace chcl
{
	template <unsigned int width, unsigned int height>
	class MatrixBase
	{
	protected:
		float m_values[width * height];

	public:
		MatrixBase(float defaultVal = 0.f)
		{
			std::fill(m_values, m_values + width * height, defaultVal);
		}

		MatrixBase(const float *values)
		{
			std::memcpy(m_values, values, width * height * sizeof(float));
		}

		MatrixBase(std::initializer_list<float> values)
		{
			std::memcpy(m_values, values.begin(), values.size() * sizeof(float));
		}

		MatrixBase(const MatrixBase& other)
			: MatrixBase(other.m_values)
		{

		}

		template <unsigned int otherWidth, unsigned int otherHeight>
		static MatrixBase<otherWidth, otherHeight> Resize(const MatrixBase &mat)
		{
			MatrixBase<otherWidth, otherHeight> result;
			for (unsigned int i = 0; i < std::min(width, otherWidth); ++i)
			{
				for (unsigned int j = 0; j < std::min(height, otherHeight); ++j)
				{
					result.at(i, j) = mat.at(i, j);
				}
			}
			return result;
		}

		float* values() { return m_values; }
		const float* values() const { return m_values; }

		const float& at(unsigned int col, unsigned int row) const { return m_values[size_t(row) * width + col]; }
		float& at(unsigned int col, unsigned int row) { return m_values[size_t(row) * width + col]; }

		MatrixBase<1, 1> getValueAsMatrix(unsigned int col, unsigned int row) const
		{
			return MatrixBase<1, 1>(at(col, row));
		}

		void getCol(unsigned int col, float* out) const
		{
			for (unsigned int i = 0; i < height; ++i)
			{
				out[i] = at(col, i);
			}
		}

		void getRow(unsigned int row, float* out) const
		{
			for (unsigned int i = 0; i < width; ++i)
			{
				out[i] = at(i, row);
			}
		}

		MatrixBase<1, height> getColAsMatrix(unsigned int col) const
		{
			MatrixBase<1, height> result;
			for (unsigned int i = 0; i < height; ++i)
			{
				result.at(0, i) = at(col, i);
			}
			return result;
		}

		MatrixBase<width, 1> getRowAsMatrix(unsigned int row) const
		{
			return MatrixBase<width, 1>(&at(0, row));
		}

		explicit operator bool() const
		{
			if (width == 0 && height == 0)
				return false;

			for (unsigned int i = width * height; i--;)
			{
				if (m_values[i] != 0)
				{
					return true;
				}
			}

			return false;
		}

		friend MatrixBase operator*(const MatrixBase &mat, float num)
		{
			MatrixBase result = mat;
			result *= num;
			return result;
		}

		friend MatrixBase operator*(float num, const MatrixBase &mat)
		{
			MatrixBase result = mat;
			result *= num;
			return result;
		}

		friend MatrixBase operator/(const MatrixBase &mat, float num)
		{
			MatrixBase result = mat;
			result /= num;
			return result;
		}

		friend MatrixBase operator+(const MatrixBase &lhs, const MatrixBase &rhs)
		{
			MatrixBase result = lhs;
			result += rhs;
			return result;
		}

		friend MatrixBase operator-(const MatrixBase &lhs, const MatrixBase &rhs)
		{
			MatrixBase result = lhs;
			result -= rhs;
			return result;
		}

		template <unsigned int otherWidth>
		friend MatrixBase<otherWidth, height> operator*(const MatrixBase &lhs, const MatrixBase<otherWidth, width> &rhs)
		{
			MatrixBase<otherWidth, height> result;
			for (unsigned int i = 0; i < height; ++i)
			{
				for (unsigned int j = 0; j < width; ++j)
				{
					for (unsigned int k = 0; k < otherWidth; ++k)
					{
						result.at(j, i) += lhs.at(k, i) * rhs.at(j, k);
					}
				}
			}
			return result;
		}

		void perValue(std::function<float(float)> func)
		{
			for (unsigned int i = height * width; i--;)
			{
				m_values[i] = func(m_values[i]);
			}
		}

		MatrixBase& operator =(std::initializer_list<float> values)
		{
			std::memcpy(m_values, values.begin(), values.size() * sizeof(float));
			return *this;
		}

		MatrixBase& operator =(float num)
		{
			std::fill(m_values, m_values + size_t(width) * height, num);
			return *this;
		}

		MatrixBase& operator*=(float num)
		{
			perValue([num](float val) { return val * num; });
			return *this;
		}

		MatrixBase& operator/=(float num)
		{
			perValue([num](float val) { return val / num; });
			return *this;
		}

		MatrixBase& operator =(const MatrixBase &other)
		{
			std::memcpy(m_values, other.m_values, size_t(width) * height * sizeof(float));
			return *this;
		}

		MatrixBase& operator+=(const MatrixBase &other)
		{
			for (unsigned int i = height * width; i--;)
			{
				m_values[i] += other.m_values[i];
			}
			return *this;
		}

		MatrixBase& operator-=(const MatrixBase &other)
		{
			for (unsigned int i = height * width; i--;)
			{
				m_values[i] -= other.m_values[i];
			}
			return *this;
		}

		friend bool operator==(const MatrixBase &lhs, const MatrixBase &rhs)
		{
			for (unsigned int i = width * height; i--;)
			{
				if (lhs.m_values[i] != rhs.m_values[i])
				{
					return false;
				}
			}

			return true;
		}

		friend bool operator!=(const MatrixBase &lhs, const MatrixBase &rhs)
		{
			return !(lhs == rhs);
		}
	};

	template <unsigned int width, unsigned int height>
	class Matrix : public MatrixBase<width, height>
	{
	public:
		using MatrixBase<width, height>::MatrixBase;

		Matrix(const MatrixBase<width, height> &other)
			: MatrixBase<width, height>(other)
		{

		}
	};
}