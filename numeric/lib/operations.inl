#include "../include/operations.hpp"

namespace nm
{
	namespace linalg
	{
		matr32f_t identity_matrix(uint128_t n)
		{
			return matr32f_t(n).fill_diagonal(1);
		}

		template<typename T>
		base_type::matrix_base<T> diagonal(const uint128_t & n, const T & value)
		{
			return base_type::matrix_base<T>(n).fill_diagonal(value);
		}

		template<typename T>
		base_type::matrix_base<T> diagonal(const base_type::vector_base<T>&values)
		{
			return base_type::matrix_base<T>(values.size()).fill_diagonal(values);
		}

		template<typename T>
		base_type::matrix_base<T> multidiagonal(const uint128_t & n, const std::initializer_list<std::pair<int32_t, T>>&values)
		{
			base_type::matrix_base<T> matrix(n);
			for (auto& pair : values)
				matrix.fill_diagonal(pair.second, pair.first);
			return matrix;
		}

		template<typename T>
		base_type::matrix_base<T> multidiagonal(const std::initializer_list<std::pair<int32_t, base_type::vector_base<T>>>&values)
		{
			base_type::matrix_base<T> matrix(values.begin()->second.size());
			for (auto& pair : values)
				matrix.fill_diagonal(pair.second, pair.first);
			return matrix;
		}

		template<typename T>
		base_type::matrix_base<T> triangulation(const base_type::matrix_base<T>&matr)
		{
			assert(matr.is_square());
			auto m = matr.rows();
			base_type::matrix_base<T> result(matr);
			for (int i = 0; i < m; i++)
			{
				/*auto imax = i;
				for (int j = i + 1; j < m; j++)
					if (result[j][j] > result[imax][imax])
						imax = j;
				std::swap(result[i], result[imax]);*/

				for (int j = i + 1; j < m; j++)
				{
					auto mul = -result[j][i] / result[i][i];
					for (int k = 0; k < m; k++)
						result[j][k] += result[i][k] * mul;
				}
			}
			return result;
		}

		template<typename T>
		T gauss_determinant(const base_type::matrix_base<T>&matr)
		{
			assert(matr.is_square());
			auto triangle = matr.is_triangle() ? matr : triangulation(matr);
			auto m = matr.rows();
			T det = 1;
			for (int i = 0; i < m; i++)
				det *= triangle[i][i];
			
			return det;
		}
	}
}