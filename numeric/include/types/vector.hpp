#pragma once
#include "../types.hpp"
#include "complex.hpp"

/***********************************************************************
 *
 *		            NumericLib vector declaration file
 *
 * Base class: vector_base (std::vector)
 * Inner type: T (any)
 *
 * Declared types:
 *      vect32f_t =  { float32_t }
 *      vect64f_t =  { float64_t }
 *      vect128f_t = { float128_t }
 * 
 *      vect64c_t =  { complex64_t }
 *      vect128c_t = { complex128_t }
 *      vect256c_t = { complex256_t }
 *
 * Base type:
 *      vectf_t =  { float_t }
 *      vectc_t = { complex_t }
 *
 * Vector variable can be represented by any other type, but full operator
 * overrides functionality works only for DECLARED_TYPES to avoid errors.
 * Anyway, you always can create new operator override by hand, but there are
 * no guarantess that library would be working properly with user types.
 * 
 * There also defined literal override, which makes it possible to use 'N'
 * literal to define a vector size N, filled by 1. Example: vect_t v = 10N.
 *
/***********************************************************************/

namespace nm
{
	namespace tybase
	{
		template <typename T>
		class matrix_base;

		template <typename T>
		class vector_base
		{
		public:
			using TYPE_ = T;

			static_assert(
				tycomp::is_floating_point<T>::value || tycomp::is_complex<T>::value,
				"template instantiation of vector must be floating or complex!"
			);

			// ******************************************************************************** CONSTRUCTION

			vector_base(uint128_t n = 0);
			vector_base(uint128_t n, const T& value);
			vector_base(const std::vector<T>& stdvect);
			vector_base(const std::initializer_list<T>& rawvect);

			vector_base& fill(T value);

			// ******************************************************************************** INTERFACE

			std::vector<T>& stdvect();
			const std::vector<T>& stdvect() const;

			// ********************************************************************************	SIZE, INDEXING

			size1D_t size() const;

			T& operator [](int128_t i);
			T& operator ()(int128_t i);

			const T& operator [](int128_t i) const;
			const T& operator ()(int128_t i) const;

			vector_base slice(int128_t beg, int128_t end, int128_t step = 1) const;

			// ******************************************************************************** SORTING

			vector_base& sort(bool ascend = true);
			vector_base sorted(bool ascend = true) const;

			// ******************************************************************************** MINMAX

			T max() const;
			T min() const;
			std::pair<T, T> minmax() const;

			size1D_t argmax() const;
			size1D_t argmin() const;
			size2D_t argminmax() const;

			// ******************************************************************************** TRANSFORMS

			// vector_base& transposed();      // must be row_vect implementation (!)
			// vector_base transposed() const; // must be row_vect implementation (!)

			vector_base& normalize();
			vector_base normalized() const;

			// ******************************************************************************** UNARY OPERATIONS

			auto abs() const;

			auto norm1() const;
			auto norm2() const;
			auto normi() const;

			// ******************************************************************************** BINARY OPERATIONS

			template <typename V> auto dot(const vector_base<V>& oth) const;
			template <typename V> auto dot(const matrix_base<V>& mat) const;	// matrix.inl (!)
			template <typename V> auto cross(const vector_base<V>& oth) const;

			// ******************************************************************************** EASY OPERATORS

			vector_base operator -() const;

			template <typename V> auto operator +(const V& val) const;
			template <typename V> auto operator -(const V& val) const;
			template <typename V> auto operator *(const V& val) const;
			template <typename V> auto operator /(const V& val) const;

			// ******************************************************************************** COMPLEX OPERATORS

			template <typename V> auto operator +(const complex_base<V>& cmp) const;
			template <typename V> auto operator -(const complex_base<V>& cmp) const;
			template <typename V> auto operator *(const complex_base<V>& cmp) const;
			template <typename V> auto operator /(const complex_base<V>& cmp) const;

			// ******************************************************************************** VECT OPERATORS

			template <typename V> auto operator +(const vector_base<V>& oth) const;
			template <typename V> auto operator -(const vector_base<V>& oth) const;

			// ******************************************************************************** SELF OPERATORS

			vector_base& operator +=(const T& value);
			vector_base& operator -=(const T& value);
			vector_base& operator *=(const T& value);
			vector_base& operator /=(const T& value);

			vector_base& operator +=(const vector_base<T>& oth);
			vector_base& operator -=(const vector_base<T>& oth);

			// ******************************************************************************** PROPERTIES

		protected:

			std::vector<T> base;

			// row/column stack vector logic (maybe in future)
			// constexpr bool row_vect;
		};
	}

	// **************************************************************************************** TYPE DEFENITIONS

	typedef tybase::vector_base<float32_t>    vect32f_t;
	typedef tybase::vector_base<float64_t>    vect64f_t;
	typedef tybase::vector_base<float128_t>   vect128f_t;

	typedef tybase::vector_base<complex64_t>  vect64c_t;
	typedef tybase::vector_base<complex128_t> vect128c_t;
	typedef tybase::vector_base<complex256_t> vect256c_t;

	#ifdef BASIC_COMP_TYPE_FLOAT32
	typedef vect32f_t vectf_t;
	typedef vect64c_t vectc_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT64
	typedef vect64f_t  vectf_t;
	typedef vect128c_t vectc_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT128
	typedef vect128f_t vectf_t;
	typedef vect256c_t vectc_t;
	#endif

	// **************************************************************************************** FUNCTIONS

	namespace linalg
	{
		template <typename T> T abs(tybase::vector_base<T> vct);

		template<typename T> auto norm1(tybase::vector_base<T> vct);
		template<typename T> auto norm2(tybase::vector_base<T> vct);
		template<typename T> auto normi(tybase::vector_base<T> vct);
	}

	template <typename T> T max(tybase::vector_base<T> vct);
	template <typename T> T min(tybase::vector_base<T> vct);

	template <typename T> size1D_t argmax(tybase::vector_base<T> vct);
	template <typename T> size1D_t argmin(tybase::vector_base<T> vct);
	template <typename T> size2D_t argminmax(tybase::vector_base<T> vct);

	template <typename T, typename V> auto dot(tybase::vector_base<T> vct1, tybase::vector_base<V> vct2);
	template <typename T, typename V> auto cross(tybase::vector_base<T> vct1, tybase::vector_base<V> vct2);

	// **************************************************************************************** LITERALS

	namespace literals
	{
		vectf_t operator "" N(uint128_t n) { return vectf_t(n, 1); }
	}

	// **************************************************************************************** TYPE COMPARING

	namespace tycomp
	{
		template <typename _Ty>
		constexpr bool is_floating_vector_v = _Is_any_of_v<remove_cv_t<_Ty>, vect32f_t, vect64f_t, vect128f_t>;

		template <typename _Ty>
		struct is_floating_vector : bool_constant<is_floating_vector_v<_Ty>> {};

		template <typename _Ty>
		constexpr bool is_complex_vector_v = _Is_any_of_v<remove_cv_t<_Ty>, vect64c_t, vect128c_t, vect256c_t>;

		template <typename _Ty>
		struct is_complex_vector : bool_constant<is_complex_vector_v<_Ty>> {};

		template <typename _Ty>
		constexpr bool is_vector_v = is_complex_vector_v<_Ty> || is_floating_vector_v<_Ty>;

		template <typename _Ty>
		struct is_vector : bool_constant<is_vector_v<_Ty>> {};
	}
}

// ******************************************************************************************** IO OVERRIDE

template <typename T> 
std::ostream& operator <<(std::ostream& out, const nm::tybase::vector_base<T>& vector);

// ******************************************************************************************** POSITIONAL OPERATORS OVERRIDE

template <typename T, typename V> auto operator +(const V& val, const nm::tybase::vector_base<T>& vct);
template <typename T, typename V> auto operator -(const V& val, const nm::tybase::vector_base<T>& vct);
template <typename T, typename V> auto operator *(const V& val, const nm::tybase::vector_base<T>& vct);
template <typename T, typename V> auto operator /(const V& val, const nm::tybase::vector_base<T>& vct);

template <typename T, typename V> auto operator +(const nm::tybase::complex_base<V>& cmp, const nm::tybase::vector_base<T>& vct);
template <typename T, typename V> auto operator -(const nm::tybase::complex_base<V>& cmp, const nm::tybase::vector_base<T>& vct);
template <typename T, typename V> auto operator *(const nm::tybase::complex_base<V>& cmp, const nm::tybase::vector_base<T>& vct);
template <typename T, typename V> auto operator /(const nm::tybase::complex_base<V>& cmp, const nm::tybase::vector_base<T>& vct);

#include "vector.inl"