#pragma once
#include "types.hpp"

namespace nm
{
	matr32f_t identity_matrix(uint128_t n);

	template <typename T> base_type::matrix_base<T> diagonal_matrix(const uint128_t& n, const T& value);
	template <typename T> base_type::matrix_base<T> diagonal_matrix(const base_type::vector_base<T>& values);

	template <typename T> base_type::matrix_base<T> multidiagonal_matrix(
		const uint128_t& n,
		const std::initializer_list<std::pair<int32_t, T>>& values);

	template <typename T> base_type::matrix_base<T> multidiagonal_matrix(
		const std::initializer_list<std::pair<int32_t, base_type::vector_base<T>>>& diagonals);
	
	
	

}

#include "../lib/operations.inl"