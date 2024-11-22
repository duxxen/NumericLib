#pragma once
#include "../types.hpp"

/***********************************************************************
 *
 *           NumbericLib complex declaration file
 *
 * Base class: complex_base
 * Inner type: T (any)
 *
 * Declared types:
 *      complex32_t	-   32 bit { float32,  float32 }  value
 *      complex64_t -   64 bit { float64,  float64 }  value
 *      complex128_t - 128 bit { float128, float128 } value
 *
 *
 * Complex variable can be represented by any other type, operator overrides
 * supports every type, which supports basic operations. Technically you can
 * define 'complex_base<USER_TYPE>', but there are no guarantees that library
 * would be working properly with user types.
 * 
 * There also defined literal overrides, which makes it possible to use 'i'
 * literal to define a complex number as: 'complex_t v = 1 + 2i'
 *
 ***********************************************************************/

namespace nm
{
	namespace tybase
	{
		template <typename T>
		struct complex_base
		{
			using TYPE_ = T;
			static_assert(
				tycomp::is_floating_point<T>::value,
				"template instantiation of complex must be floating!"
			);

			// ******************************************************************************** CONSTRUCTION

			complex_base(
				const T& re = 0,
				const T& im = 0
			);

			template <typename V>
			complex_base(const complex_base<V>& oth);

			// ******************************************************************************** TRANSFORMS

			complex_base inversed() const;
			complex_base conjugate() const;

			// ******************************************************************************** UNARY OPERATIONS

			T abs() const;
			T arg() const;

			// ******************************************************************************** EASY OPERATORS

			complex_base operator-() const;

			template <typename V> auto operator +(const V& value) const;
			template <typename V> auto operator -(const V& value) const;
			template <typename V> auto operator *(const V& value) const;
			template <typename V> auto operator /(const V& value) const;

			// ******************************************************************************** COMPLEX OPERATORS

			template <typename V> auto operator +(const complex_base<V>& oth) const;
			template <typename V> auto operator -(const complex_base<V>& oth) const;
			template <typename V> auto operator *(const complex_base<V>& oth) const;
			template <typename V> auto operator /(const complex_base<V>& oth) const;

			// ******************************************************************************** SELF OPERATORS

			template <typename V> complex_base& operator +=(const V& value);
			template <typename V> complex_base& operator -=(const V& value);
			template <typename V> complex_base& operator *=(const V& value);
			template <typename V> complex_base& operator /=(const V& value);

			template <typename V> complex_base& operator +=(const complex_base<V>& oth);
			template <typename V> complex_base& operator -=(const complex_base<V>& oth);
			template <typename V> complex_base& operator *=(const complex_base<V>& oth);
			template <typename V> complex_base& operator /=(const complex_base<V>& oth);

			// ******************************************************************************** COMPARE OPERATORS

			template <typename V> bool operator ==(const complex_base<V>& oth) const;
			template <typename V> bool operator !=(const complex_base<V>& oth) const;

			template <typename V> bool operator ==(const V& value) const;
			template <typename V> bool operator !=(const V& value) const;

			// ******************************************************************************** PROPERTIES

			T real;
			T imag;
		};
	}

	// **************************************************************************************** TYPE DEFENITIONS

	typedef tybase::complex_base<float32_t>	 complex64_t;
	typedef tybase::complex_base<float64_t>	 complex128_t;
	typedef tybase::complex_base<float128_t> complex256_t;

	#ifdef BASIC_COMP_TYPE_FLOAT32
	typedef complex64_t complex_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT64
	typedef complex128_t complex_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT128
	typedef complex256_t complex_t;
	#endif

	// **************************************************************************************** FUNCTIONS

	template <typename T> T abs(tybase::complex_base<T> value);
	template <typename T> T arg(tybase::complex_base<T> value);

	// **************************************************************************************** LITERALS

	namespace literals
	{
		complex_t operator "" i(float128_t v) { return complex_t(0, v); }
		complex_t operator "" i(uint128_t v) { return complex_t(0, v); }
	}

	// **************************************************************************************** TYPE COMPARING

	namespace tycomp
	{
		template <typename _Ty>
		constexpr bool is_complex_v = _Is_any_of_v<remove_cv_t<_Ty>, complex64_t, complex128_t, complex256_t>;

		template <typename _Ty>
		struct is_complex : bool_constant<is_complex_v<_Ty>> {};

		template <typename _Ty, typename _Vy>
		constexpr bool is_stronger_v = (
			is_complex<_Ty>() && is_floating_point<_Vy>() ||
			sizeof(_Ty) > sizeof(_Vy)
			);

		template <typename _Ty, typename _Vy>
		struct is_stronger : bool_constant<is_stronger_v<_Ty, _Vy>> {};
	}
}

// ******************************************************************************************** IO OVERRIDE

template <typename T>
std::ostream& operator<<(std::ostream& out, const nm::tybase::complex_base<T>& value);

// ******************************************************************************************** POSITIONAL OPERATORS OVERRIDE

template <typename T, typename V> auto operator +(const V& value, const nm::tybase::complex_base<T>& c);
template <typename T, typename V> auto operator -(const V& value, const nm::tybase::complex_base<T>& c);
template <typename T, typename V> auto operator *(const V& value, const nm::tybase::complex_base<T>& c);
template <typename T, typename V> auto operator /(const V& value, const nm::tybase::complex_base<T>& c);

#include "complex.inl"