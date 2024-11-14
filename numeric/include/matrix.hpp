#pragma once
#include "types.hpp"
#include "vector.hpp"

/***********************************************************************
 *
 *		            NumericLib vector declaration file
 *
 * Base class: vector_base (std::vector)
 * Inner type: T (any)
 *
 * Declared types:
 *      vect32_t =  { float32_t }
 *      vect64_t =  { float64_t }
 *      vect128_t = { float128_t }
 *
 * Base type:
 *      vect_t =  { float_t }
 *      vectc_t = { complex_t }
 *
 * Vector variable can be represented by any other type, but full operator
 * overrides functionality works only for DECLARED_TYPES to avoid errors.
 * Anyway, you always can create new operator override by hand, but there are
 * no guarantess that library would be working properly with user types.
 *
 * Basic operations, such as 'abs', 'norm', 'dot', etc declared at 'operations.hpp'.
 * There also defined literal override, which makes it possible to use 'N'
 * literal to define a vector size N, filled by 1. Example: vect_t v = 10N.
 *
/***********************************************************************/

namespace nm
{
	namespace base_type
	{
		template <typename T>
		struct matrix_base
		{
			static_assert(
				typing::is_floating_point<T>::value || typing::is_complex<T>::value,
				"template instantiation of matrix must be floating or complex!"
				);

			matrix_base(uint128_t mn = 0);
			matrix_base(uint128_t m, uint128_t n);
			matrix_base(uint128_t m, uint128_t n, T value);
			matrix_base(const std::vector<std::vector<T>>& stdmatr);
			matrix_base(const std::initializer_list<std::initializer_list<T>>& rawmatr);

			uint128_t rows() const;
			uint128_t cols() const;
			std::pair<uint128_t, uint128_t> size() const;

			vector_base<T>& row(int i);
			const vector_base<T>& row(int i) const;

			vector_base<T> col(int i) const;

			vector_base<T>& operator [](int i);
			const vector_base<T>& operator [](int i) const;

			matrix_base operator -() const;

			template <typename V> auto operator +(const matrix_base<V>& oth) const;
			template <typename V> auto operator -(const matrix_base<V>& oth) const;
			template <typename V> auto operator *(const matrix_base<V>& oth) const;

			matrix_base& operator +=(const matrix_base<T>& oth);
			matrix_base& operator -=(const matrix_base<T>& oth);
			matrix_base& operator *=(const matrix_base<T>& oth);

			template <typename V> auto operator +(const V& value) const;
			template <typename V> auto operator -(const V& value) const;
			template <typename V> auto operator *(const V& value) const;
			template <typename V> auto operator /(const V& value) const;

			template <typename V> auto operator +(const complex_base<V>& value) const;
			template <typename V> auto operator -(const complex_base<V>& value) const;
			template <typename V> auto operator *(const complex_base<V>& value) const;
			template <typename V> auto operator /(const complex_base<V>& value) const;

			matrix_base& operator +=(const T& value);
			matrix_base& operator -=(const T& value);
			matrix_base& operator *=(const T& value);
			matrix_base& operator /=(const T& value);


			std::vector<vector_base<T>> base;
		};
	}

	typedef base_type::matrix_base<float32_t>		matr32f_t;
	typedef base_type::matrix_base<float64_t>		matr64f_t;
	typedef base_type::matrix_base<float128_t>		matr128f_t;

	typedef base_type::matrix_base<complex32_t>		matr32c_t;
	typedef base_type::matrix_base<complex64_t>		matr64c_t;
	typedef base_type::matrix_base<complex128_t>	matr128c_t;

	#ifdef BASIC_COMP_TYPE_FLOAT32
	typedef matr32f_t matrf_t;
	typedef matr32c_t matrc_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT64
	typedef matr64f_t matrf_t;
	typedef matr64c_t matrc_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT128
	typedef matr128f_t matrf_t;
	typedef matr128c_t matrc_t;
	#endif

	namespace typing
	{
		template <typename _Ty>
		constexpr bool is_floating_matrix_v = _Is_any_of_v<remove_cv_t<_Ty>, matr32f_t, matr64f_t, matr128f_t>;

		template <typename _Ty>
		struct is_floating_matrix : bool_constant<is_floating_matrix_v<_Ty>> {};

		template <typename _Ty>
		constexpr bool is_complex_matrix_v = _Is_any_of_v<remove_cv_t<_Ty>, matr32c_t, matr64c_t, matr128c_t>;

		template <typename _Ty>
		struct is_complex_matrix : bool_constant<is_complex_matrix_v<_Ty>> {};

		template <typename _Ty>
		constexpr bool is_matrix_v = is_complex_matrix_v<_Ty> || is_floating_matrix_v<_Ty>;

		template <typename _Ty>
		struct is_matrix : bool_constant<is_matrix_v<_Ty>> {};
	}
}

template <typename T> std::ostream& operator <<(std::ostream& out, const nm::base_type::matrix_base<T>& matrix);

template <typename T, typename V> auto operator +(const V& value, const nm::base_type::matrix_base<T>& matrix);
template <typename T, typename V> auto operator -(const V& value, const nm::base_type::matrix_base<T>& matrix);
template <typename T, typename V> auto operator *(const V& value, const nm::base_type::matrix_base<T>& matrix);
template <typename T, typename V> auto operator /(const V& value, const nm::base_type::matrix_base<T>& matrix);

template <typename T, typename V> auto operator +(const nm::base_type::complex_base<V>& value, const nm::base_type::matrix_base<T>& matrix);
template <typename T, typename V> auto operator -(const nm::base_type::complex_base<V>& value, const nm::base_type::matrix_base<T>& matrix);
template <typename T, typename V> auto operator *(const nm::base_type::complex_base<V>& value, const nm::base_type::matrix_base<T>& matrix);
template <typename T, typename V> auto operator /(const nm::base_type::complex_base<V>& value, const nm::base_type::matrix_base<T>& matrix);

#include "../lib/matrix.inl"