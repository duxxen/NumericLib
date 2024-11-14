#pragma once
#include "types.hpp"

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
 * Basic operations, such as 'abs', 'arg', etc declared at 'operations.hpp'.
 * There also defined literal overrides, which makes it possible to use 'i'
 * literal to define a complex number as: 'complex_t v = 1 + 2i'
 * 
 ***********************************************************************/

namespace nm
{
	namespace base_type
	{
		template <typename T>
		struct complex_base
		{
			static_assert(
				typing::is_floating_point<T>::value, 
				"template instantiation of complex must be floating!"
			);

			complex_base(
				const T& re = 0,
				const T& im = 0
			);

			template <typename V>
			complex_base(const complex_base<V>& oth);

			T abs() const;
			T arg() const;

			complex_base inversed() const;
			complex_base conjugated() const;

			complex_base operator-() const;

			template <typename V> auto operator +(const complex_base<V>& oth) const;
			template <typename V> auto operator -(const complex_base<V>& oth) const;
			template <typename V> auto operator *(const complex_base<V>& oth) const;
			template <typename V> auto operator /(const complex_base<V>& oth) const;

			template <typename V> complex_base& operator +=(const complex_base<V>& oth);
			template <typename V> complex_base& operator -=(const complex_base<V>& oth);
			template <typename V> complex_base& operator *=(const complex_base<V>& oth);
			template <typename V> complex_base& operator /=(const complex_base<V>& oth);

			template <typename V> auto operator +(const V& value) const;
			template <typename V> auto operator -(const V& value) const;
			template <typename V> auto operator *(const V& value) const;
			template <typename V> auto operator /(const V& value) const;

			template <typename V> complex_base& operator +=(const V& value);
			template <typename V> complex_base& operator -=(const V& value);
			template <typename V> complex_base& operator *=(const V& value);
			template <typename V> complex_base& operator /=(const V& value);

			T real;
			T imag;
		};
	}

	typedef base_type::complex_base<float32_t>	complex32_t;
	typedef base_type::complex_base<float64_t>	complex64_t;
	typedef base_type::complex_base<float128_t>	complex128_t;

	#ifdef BASIC_COMP_TYPE_FLOAT32
	typedef complex32_t complex_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT64
	typedef complex64_t complex_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT128
	typedef complex128_t complex_t;
	#endif

	namespace literals
	{
		complex_t operator "" i(float128_t v) { return complex_t(0, v); }
		complex_t operator "" i(uint128_t v) { return complex_t(0, v); }
	}

	namespace typing
	{
		template <typename _Ty>
		constexpr bool is_complex_v = _Is_any_of_v<remove_cv_t<_Ty>, complex32_t, complex64_t, complex128_t>;

		template <typename _Ty>
		struct is_complex : bool_constant<is_complex_v<_Ty>> {};

		template <typename _Ty, typename _Vy>
		constexpr bool is_stronger_v = (
			nm::typing::is_complex<_Ty>() && is_floating_point<_Vy>() ||
			sizeof(_Ty) > sizeof(_Vy)
			);

		template <typename _Ty, typename _Vy>
		struct is_stronger : bool_constant<is_stronger_v<_Ty, _Vy>> {};
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const nm::base_type::complex_base<T>& value);

template <typename T, typename V> auto operator +(const V& value, const nm::base_type::complex_base<T>& c);
template <typename T, typename V> auto operator -(const V& value, const nm::base_type::complex_base<T>& c);
template <typename T, typename V> auto operator *(const V& value, const nm::base_type::complex_base<T>& c);
template <typename T, typename V> auto operator /(const V& value, const nm::base_type::complex_base<T>& c);

#include "../lib/complex.inl"
