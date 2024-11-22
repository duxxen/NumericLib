#pragma once
#include "../types.hpp"
#include "complex.hpp"
#include "vector.hpp"

/***********************************************************************
 *
 *		            NumericLib matrix declaration file
 *
 * Base class: matrix_base (vector_base)
 * Inner type: T (any)
 *
 * Declared types:
 *      matr32f_t =  { float32_t }
 *      matr64f_t =  { float64_t }
 *      matr128f_t = { float128_t }
 * 
 *      matr64c_t =  { complex64_t }
 *      matr128c_t = { complex128_t }
 *      matr256c_t = { complex256_t }
 *
 * Base type:
 *      matrf_t = { float_t }
 *      matrc_t = { complex_t }
 *
 *
/***********************************************************************/

namespace nm
{
	namespace tybase
	{
		template <typename T>
		class matrix_base : public vector_base<T>
		{
		public:

			// ******************************************************************************** CONSTRUCTION

			matrix_base(uint128_t mn = 0);
			matrix_base(uint128_t m, uint128_t n);
			matrix_base(uint128_t m, uint128_t n, T value);

			matrix_base(const vector_base<T>& nmvect); // checkout (!)
			matrix_base(const std::vector<std::vector<T>>& stdmatr);
			matrix_base(const std::initializer_list<std::initializer_list<T>>& rawmatr);

			matrix_base& fill(T value);
			matrix_base& fill_diagonal(T value, int32_t index = 0);
			matrix_base& fill_diagonal(vector_base<T> values, int32_t index = 0);

			// ******************************************************************************** SIZE

			size1D_t rows() const;
			size1D_t cols() const;
			size2D_t size() const;

			// ******************************************************************************** INDEXING

			T& operator ()(int128_t i, int128_t j);
			const T& operator ()(int128_t i, int128_t j) const;
			
			vector_base<T> row(int128_t i);
			vector_base<T> col(int128_t i) const;
			vector_base<T> diagonal(int128_t i) const;

			matrix_base slice(int32_t rbeg, int32_t rend, int32_t cbeg, int32_t cend,
				int32_t rstep = 1, int32_t cstep = 1);

			// ******************************************************************************** MINMAX

			size2D_t argmax() const;
			size2D_t argmin() const;
			std::pair<size2D_t, size2D_t> argminmax() const;

			// ******************************************************************************** TRANSFORMS

			matrix_base& normalize();
			matrix_base normalized() const;

			matrix_base& transpose();
			matrix_base transposed() const;

			matrix_base inversed() const;

			// ******************************************************************************** UNARY OPERATIONS

			auto det() const;

			auto norm1() const;
			auto norm2() const;
			auto normi() const;

			// ******************************************************************************** BINARY OPERATIONS

			template <typename V> auto dot(matrix_base<V>& oth) const;
			template <typename V> auto dot(vector_base<V>& vct) const;

			// ******************************************************************************** EASY OPERATORS

			matrix_base operator -() const;

			template <typename V> auto operator +(const V& value) const;
			template <typename V> auto operator -(const V& value) const;
			template <typename V> auto operator *(const V& value) const;
			template <typename V> auto operator /(const V& value) const;

			// ******************************************************************************** COMPLEX OPERATORS

			template <typename V> auto operator +(const complex_base<V>& value) const;
			template <typename V> auto operator -(const complex_base<V>& value) const;
			template <typename V> auto operator *(const complex_base<V>& value) const;
			template <typename V> auto operator /(const complex_base<V>& value) const;

			// ******************************************************************************** MATR OPERATORS

			template <typename V> auto operator +(const matrix_base<V>& oth) const;
			template <typename V> auto operator -(const matrix_base<V>& oth) const;
			template <typename V> auto operator *(const matrix_base<V>& oth) const;

			// ******************************************************************************** VECT OPERATORS

			// template <typename V> auto operator +(const vector_base<V>& vct) const; // must be row_vect implementation (!)
			// template <typename V> auto operator -(const vector_base<V>& vct) const; // must be row_vect implementation (!)
			template <typename V> auto operator *(const vector_base<V>& vct) const;
			template <typename V> auto operator *(const vector_base<complex_base<V>>& vct) const;

			// ******************************************************************************** SELF OPERATORS

			matrix_base& operator +=(const T& value);
			matrix_base& operator -=(const T& value);
			matrix_base& operator *=(const T& value);
			matrix_base& operator /=(const T& value);

			matrix_base& operator +=(const matrix_base<T>& oth);
			matrix_base& operator -=(const matrix_base<T>& oth);

		private:
		};
	}

	// **************************************************************************************** TYPE DEFENITIONS

	typedef tybase::matrix_base<float32_t>    matr32f_t;
	typedef tybase::matrix_base<float64_t>    matr64f_t;
	typedef tybase::matrix_base<float128_t>   matr128f_t;

	typedef tybase::matrix_base<complex64_t>  matr64c_t;
	typedef tybase::matrix_base<complex128_t> matr128c_t;
	typedef tybase::matrix_base<complex256_t> matr256c_t;

	#ifdef BASIC_COMP_TYPE_FLOAT32
	typedef matr32f_t matrf_t;
	typedef matr64c_t matrc_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT64
	typedef matr64f_t  matrf_t;
	typedef matr128c_t matrc_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT128
	typedef matr128f_t matrf_t;
	typedef matr256c_t matrc_t;
	#endif

	// **************************************************************************************** FUNCTIONS

	namespace linalg
	{
		template <typename T> T det(tybase::matrix_base<T> vct);

		template<typename T> auto norm1(tybase::matrix_base<T> vct);
		template<typename T> auto norm2(tybase::matrix_base<T> vct);
		template<typename T> auto normi(tybase::matrix_base<T> vct);

		template <typename T> size2D_t argmax(tybase::matrix_base<T> vct);
		template <typename T> size2D_t argmin(tybase::matrix_base<T> vct);
		template <typename T> std::pair<size2D_t, size2D_t> argminmax(tybase::matrix_base<T> vct);

		template <typename T, typename V> auto dot(tybase::matrix_base<T> mtr1, tybase::matrix_base<V> mtr2);
		template <typename T, typename V> auto dot(tybase::matrix_base<T> mtr, tybase::vector_base<V> vct);
		template <typename T, typename V> auto dot(tybase::vector_base<T> vct, tybase::matrix_base<V> mtr);
	}

	// **************************************************************************************** TYPE COMPARING

	namespace tycomp
	{
		template <typename _Ty>
		constexpr bool is_floating_matrix_v = _Is_any_of_v<remove_cv_t<_Ty>, matr32f_t, matr64f_t, matr128f_t>;

		template <typename _Ty>
		struct is_floating_matrix : bool_constant<is_floating_matrix_v<_Ty>> {};

		template <typename _Ty>
		constexpr bool is_complex_matrix_v = _Is_any_of_v<remove_cv_t<_Ty>, matr64c_t, matr128c_t, matr256c_t>;

		template <typename _Ty>
		struct is_complex_matrix : bool_constant<is_complex_matrix_v<_Ty>> {};

		template <typename _Ty>
		constexpr bool is_matrix_v = is_complex_matrix_v<_Ty> || is_floating_matrix_v<_Ty>;

		template <typename _Ty>
		struct is_matrix : bool_constant<is_matrix_v<_Ty>> {};
	}
}

// ******************************************************************************************** IO OVERRIDE

template <typename T> std::ostream& operator <<(std::ostream& out, const nm::tybase::matrix_base<T>& matrix);

// ******************************************************************************************** POSITIONAL OPERATORS OVERRIDE

template <typename T, typename V> auto operator +(const V& val, const nm::tybase::matrix_base<T>& mtr);
template <typename T, typename V> auto operator -(const V& val, const nm::tybase::matrix_base<T>& mtr);
template <typename T, typename V> auto operator *(const V& val, const nm::tybase::matrix_base<T>& mtr);
template <typename T, typename V> auto operator /(const V& val, const nm::tybase::matrix_base<T>& mtr);

template <typename T, typename V> auto operator +(const nm::tybase::complex_base<V>& cmp, const nm::tybase::matrix_base<T>& mtr);
template <typename T, typename V> auto operator -(const nm::tybase::complex_base<V>& cmp, const nm::tybase::matrix_base<T>& mtr);
template <typename T, typename V> auto operator *(const nm::tybase::complex_base<V>& cmp, const nm::tybase::matrix_base<T>& mtr);
template <typename T, typename V> auto operator /(const nm::tybase::complex_base<V>& cmp, const nm::tybase::matrix_base<T>& mtr);

template <typename T, typename V> auto operator *(const nm::tybase::vector_base<V>& vct, const nm::tybase::matrix_base<T>& mtr);
template <typename T, typename V> auto operator *(const nm::tybase::vector_base<nm::tybase::complex_base<V>>& vct, const nm::tybase::matrix_base<T>& mtr);
