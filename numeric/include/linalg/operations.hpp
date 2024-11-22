#pragma once
#include "../types.hpp"
#include "../types/complex.hpp"
#include "../types/vector.hpp"
#include "../types/matrix.hpp"

namespace nm
{
	namespace linalg
	{
		// **************************************************************************************** VECTOR

		template <typename T> T abs(const tybase::vector_base<T>& vct);

		template<typename T> auto norm1(const tybase::vector_base<T>& vct);
		template<typename T> auto norm2(const tybase::vector_base<T>& vct);
		template<typename T> auto normi(const tybase::vector_base<T>& vct);

		// **************************************************************************************** MATRIX

		template <typename T> T det(const tybase::matrix_base<T>& mtr);
		template <typename T> T gauss_det(const tybase::matrix_base<T>& matr, bool triangle_check = true);

		template<typename T> auto norm1(const tybase::matrix_base<T>& mtr);
		template<typename T> auto norm2(const tybase::matrix_base<T>& mtr);
		template<typename T> auto normi(const tybase::matrix_base<T>& mtr);
	}

	// ******************************************************************************************** IDENTITY MATRICES

	matrf_t identity(size1D_t n);
	matrf_t triangle_l(size1D_t n);
	matrf_t triangle_u(size1D_t n);

	// ******************************************************************************************** VECTOR CREATION

	template <typename T> tybase::vector_base<T> arrange(const T& beg, const T& end, const T& step);
	template <typename T> tybase::vector_base<T> linspace(const T& beg, const T& end, size1D_t n);

	// ******************************************************************************************** MATRIX CREATION

	template <typename T> tybase::matrix_base<T> diagonal(size1D_t n, const T& value);
	template <typename T> tybase::matrix_base<T> diagonal(const tybase::vector_base<T>& values);

	template <typename T>
	tybase::matrix_base<T> multidiagonal(
		const size1D_t& n,
		const std::initializer_list<std::pair<int32_t, T>>& values
	);

	template <typename T> 
	tybase::matrix_base<T> multidiagonal(
		const std::initializer_list<std::pair<int32_t, tybase::vector_base<T>>>& diagonals
	);

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

	template <typename T, typename V> auto dot(const tybase::vector_base<T>& vct1, const tybase::vector_base<V>& vct2);
	template <typename T, typename V> auto cross(const tybase::vector_base<T>& vct1, const tybase::vector_base<V>& vct2);

	// ******************************************************************************************** MULTI PRODUCT

	template <typename T, typename... Rest>
	auto multidot(const tybase::vector_base<T> vct, const Rest&... rest);
}