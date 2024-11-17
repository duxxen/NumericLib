#pragma once
#include "types.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "complex.hpp"

namespace nm
{
	namespace linalg
	{
		matr32f_t identity_matrix(uint128_t n);

		template <typename T> base_type::matrix_base<T> diagonal(const uint128_t& n, const T& value);
		template <typename T> base_type::matrix_base<T> diagonal(const base_type::vector_base<T>& values);

		template <typename T> base_type::matrix_base<T> multidiagonal(
			const uint128_t& n,
			const std::initializer_list<std::pair<int32_t, T>>& values);

		template <typename T> base_type::matrix_base<T> multidiagonal(
			const std::initializer_list<std::pair<int32_t, base_type::vector_base<T>>>& diagonals);

		template <typename T> base_type::matrix_base<T> triangulation(const base_type::matrix_base<T>& matr);

		template <typename T> T gauss_determinant(const base_type::matrix_base<T>& matr);

		// returns C = L + U - E matrix
		template <typename T> base_type::matrix_base<T> LU_decomposion(const base_type::matrix_base<T>& matr);

		// returns { C = (L + U - E), P } matrices
		template <typename T> std::tuple<base_type::matrix_base<T>, base_type::matrix_base<T>> LUP_decomposion(const base_type::matrix_base<T>& matr);
	}
	
	

}

#include "../lib/operations.inl"