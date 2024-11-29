#pragma once
#include "../types.hpp"
#include "../types/complex.hpp"
#include "../types/vector.hpp"
#include "../types/matrix.hpp"
#include "decomposion.hpp"

namespace nm
{
	namespace linalg
	{
		// **************************************************************************************** VECTOR

		template<typename T> auto norm1(const tybase::vector_base<T>& vct);
		template<typename T> auto norm2(const tybase::vector_base<T>& vct);
		template<typename T> auto normi(const tybase::vector_base<T>& vct);
		template<typename T> auto norme(const tybase::vector_base<T>& vct);
		template<typename T> auto normp(const uint128_t& p, const tybase::vector_base<T>& vct);

		// **************************************************************************************** MATRIX

		template <typename T> T det(const tybase::matrix_base<T>& mtr);
		template <typename T> T gauss_det(const tybase::matrix_base<T>& matr, bool triangle_check = true);

		template<typename T> auto norm1(const tybase::matrix_base<T>& mtr);
		template<typename T> auto norm2(const tybase::matrix_base<T>& mtr);
		template<typename T> auto normi(const tybase::matrix_base<T>& mtr);
		template<typename T> auto norme(const tybase::matrix_base<T>& vct);
		template<typename T> auto normp(const uint128_t& p, const tybase::matrix_base<T>& vct);
		template<typename T> auto normp(const uint128_t& p, const uint128_t& q, const tybase::matrix_base<T>& vct);
	}

	// **************************************************************************************** POWER

	template <typename T> tybase::vector_base<T> pow(const tybase::vector_base<T>& vct, float_t p);
	template <typename T> tybase::matrix_base<T> pow(const tybase::matrix_base<T>& mtr, int64_t p);

	// **************************************************************************************** ABSOLUTE, ARGUMENT

	template <typename T> T abs(const tybase::vector_base<T>& vct);
	template <typename T> T abs(const tybase::matrix_base<T>& mtr);

	template <typename T> T abs(const tybase::complex_base<T>& value);
	template <typename T> T arg(const tybase::complex_base<T>& value);

	// ******************************************************************************************** MINMAX

	template <typename T> T max(const tybase::vector_base<T>& vct);
	template <typename T> T min(const tybase::vector_base<T>& vct);

	template <typename T> size1D_t argmax(const tybase::vector_base<T>& vct);
	template <typename T> size1D_t argmin(const tybase::vector_base<T>& vct);
	template <typename T> size2D_t argminmax(const tybase::vector_base<T>& vct);

	template <typename T> size2D_t argmax(const tybase::matrix_base<T>& vct);
	template <typename T> size2D_t argmin(const tybase::matrix_base<T>& vct);
	template <typename T> std::pair<size2D_t, size2D_t> argminmax(const tybase::matrix_base<T>& vct);

	// ******************************************************************************************** VECTOR PRODUCT

	template <typename T, typename V> auto dot(const tybase::vector_base<T>& vct1, const tybase::vector_base<V>& vct2);
	template <typename T, typename V> auto cross(const tybase::vector_base<T>& vct1, const tybase::vector_base<V>& vct2);

	// ******************************************************************************************** MATRIX PRODUCT

	template <typename T, typename V> auto dot(const tybase::matrix_base<T>& mtr1, const tybase::matrix_base<V>& mtr2);
	template <typename T, typename V> auto dot(const tybase::matrix_base<T>& mtr, const tybase::vector_base<V>& vct);
	template <typename T, typename V> auto dot(const tybase::vector_base<T>& vct, const tybase::matrix_base<V>& mtr);

	// ******************************************************************************************** MULTI PRODUCT

	template <typename T, typename... Rest>
	auto multidot(const tybase::vector_base<T> vct, const Rest&... rest);
}

#include "operations.inl"