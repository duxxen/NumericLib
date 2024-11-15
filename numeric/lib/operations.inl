#include "../include/operations.hpp"

namespace nm
{
	matr32f_t nm::identity_matrix(uint128_t n)
	{
		return matr32f_t(n).fill_diagonal(1);
	}

	template<typename T>
	base_type::matrix_base<T> diagonal_matrix(const uint128_t& n, const T& value)
	{
		return base_type::matrix_base<T>(n).fill_diagonal(value);
	}

	template<typename T>
	base_type::matrix_base<T> diagonal_matrix(const base_type::vector_base<T>& values)
	{
		return base_type::matrix_base<T>(values.size()).fill_diagonal(values);
	}

	template<typename T>
	base_type::matrix_base<T> multidiagonal_matrix(const uint128_t& n, const std::initializer_list<std::pair<int32_t, T>>& values)
	{
		base_type::matrix_base<T> matrix(n);
		for (auto& pair : values)
			matrix.fill_diagonal(pair.second, pair.first);
		return matrix;
	}

	template<typename T>
	base_type::matrix_base<T> multidiagonal_matrix(const std::initializer_list<std::pair<int32_t, base_type::vector_base<T>>>& values)
	{
		base_type::matrix_base<T> matrix(values.begin()->second.size());
		for (auto& pair : values)
			matrix.fill_diagonal(pair.second, pair.first);
		return matrix;
	}
}