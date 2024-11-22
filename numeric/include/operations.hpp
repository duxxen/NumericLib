#pragma once
#include "types.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "complex.hpp"

namespace nm
{
	template <typename T, typename V> auto dot(base_type::matrix_base<T> mtr1, base_type::matrix_base<T> mtr2);
	template <typename T, typename V> auto dot(base_type::vector_base<T> vct1, base_type::vector_base<T> vct2);
	template <typename T, typename V> auto dot(base_type::matrix_base<T> mtr, base_type::vector_base<T> vct);
	template <typename T, typename V> auto dot(base_type::vector_base<T> vct, base_type::matrix_base<T> mtr);

	template <typename T> T max(base_type::matrix_base<T> mtr);
	template <typename T> T max(base_type::vector_base<T> vct);
	template <typename T> T min(base_type::matrix_base<T> mtr);
	template <typename T> T min(base_type::vector_base<T> vct);

	template <typename T> uint128_t argmax(base_type::vector_base<T> vct);
	template <typename T> uint128_t argmin(base_type::vector_base<T> vct);
	template <typename T> std::pair<uint128_t, uint128_t> argmax(base_type::matrix_base<T> mtr);
	template <typename T> std::pair<uint128_t, uint128_t> argmin(base_type::matrix_base<T> mtr);

	template <typename T> T abs(base_type::vector_base<T> vct);
	template <typename T> T det(base_type::matrix_base<T> mtr);
	//template <typename T> T abs(base_type::complex_base<T> cmp);	// defined at complex.hpp
}

#include "../lib/operations.inl"