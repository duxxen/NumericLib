#pragma once
#include "types.hpp"
#include "complex.hpp"

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
		struct vector_base
		{
			static_assert(
				typing::is_floating_point<T>::value || typing::is_complex<T>::value,
				"template instantiation of vector must be floating or complex!"
			);

			vector_base(uint128_t n = 0);
			vector_base(uint128_t n, T value);
			vector_base(const std::vector<T>& stdvect);
			vector_base(const std::initializer_list<T>& rawvect);

			uint128_t size() const;

			T abs() const;

			vector_base& normalize();
			vector_base normalized() const;

			T& operator [](int i);
			const T& operator [](int i) const;

			vector_base operator -() const;

			template <typename V> auto operator +(const vector_base<V>& oth) const;
			template <typename V> auto operator -(const vector_base<V>& oth) const;

			vector_base& operator +=(const vector_base<T>& oth);
			vector_base& operator -=(const vector_base<T>& oth);

			template <typename V> auto operator +(const V& value) const;
			template <typename V> auto operator -(const V& value) const;
			template <typename V> auto operator *(const V& value) const;
			template <typename V> auto operator /(const V& value) const;

			template <typename V> auto operator +(const complex_base<V>& value) const;
			template <typename V> auto operator -(const complex_base<V>& value) const;
			template <typename V> auto operator *(const complex_base<V>& value) const;
			template <typename V> auto operator /(const complex_base<V>& value) const;

			vector_base& operator +=(const T& value);
			vector_base& operator -=(const T& value);
			vector_base& operator *=(const T& value);
			vector_base& operator /=(const T& value);


			std::vector<T> base;
		};
	}

	typedef base_type::vector_base<float32_t>		vect32f_t;
	typedef base_type::vector_base<float64_t>		vect64f_t;
	typedef base_type::vector_base<float128_t>		vect128f_t;

	typedef base_type::vector_base<complex32_t>		vect32c_t;
	typedef base_type::vector_base<complex64_t>		vect64c_t;
	typedef base_type::vector_base<complex128_t>	vect128c_t;

	#ifdef BASIC_COMP_TYPE_FLOAT32
	typedef vect32f_t vectf_t;
	typedef vect32c_t vectc_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT64
	typedef vect64f_t vectf_t;
	typedef vect64c_t vectc_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT128
	typedef vect128f_t vectf_t;
	typedef vect128c_t vectc_t;
	#endif

	namespace literals
	{
		vectf_t operator "" N(uint128_t n) { return vectf_t(n, 1); }
	}

	namespace typing
	{
		template <typename _Ty>
		constexpr bool is_floating_vector_v = _Is_any_of_v<remove_cv_t<_Ty>, vect32f_t, vect64f_t, vect128f_t>;

		template <typename _Ty>
		struct is_floating_vector : bool_constant<is_floating_vector_v<_Ty>> {};

		template <typename _Ty>
		constexpr bool is_complex_vector_v = _Is_any_of_v<remove_cv_t<_Ty>, vect32c_t, vect64c_t, vect128c_t>;

		template <typename _Ty>
		struct is_complex_vector : bool_constant<is_complex_vector_v<_Ty>> {};

		template <typename _Ty>
		constexpr bool is_vector_v = is_complex_vector_v<_Ty> || is_floating_vector_v<_Ty>;

		template <typename _Ty>
		struct is_vector : bool_constant<is_vector_v<_Ty>> {};
	}
}

template <typename T> std::ostream& operator <<(std::ostream& out, const nm::base_type::vector_base<T>& vector);

template <typename T, typename V> auto operator +(const V& value, const nm::base_type::vector_base<T>& vector);
template <typename T, typename V> auto operator -(const V& value, const nm::base_type::vector_base<T>& vector);
template <typename T, typename V> auto operator *(const V& value, const nm::base_type::vector_base<T>& vector);
template <typename T, typename V> auto operator /(const V& value, const nm::base_type::vector_base<T>& vector);

template <typename T, typename V> auto operator +(const nm::base_type::complex_base<V>& value, const nm::base_type::vector_base<T>& vector);
template <typename T, typename V> auto operator -(const nm::base_type::complex_base<V>& value, const nm::base_type::vector_base<T>& vector);
template <typename T, typename V> auto operator *(const nm::base_type::complex_base<V>& value, const nm::base_type::vector_base<T>& vector);
template <typename T, typename V> auto operator /(const nm::base_type::complex_base<V>& value, const nm::base_type::vector_base<T>& vector);

#include "../lib/vector.inl"


