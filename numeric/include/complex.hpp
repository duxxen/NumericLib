#pragma once
#include "types.hpp"

namespace nm
{
	template <typename T>
	struct complex
	{
		complex(
			const T& re = 0,
			const T& im = 0
		);

		complex operator-() const;

		template <typename V> complex operator +(const complex<V>& oth) const;
		template <typename V> complex operator -(const complex<V>& oth) const;
		template <typename V> complex operator *(const complex<V>& oth) const;
		template <typename V> complex operator /(const complex<V>& oth) const;

		template <typename V> complex& operator +=(const complex<V>& oth);
		template <typename V> complex& operator -=(const complex<V>& oth);
		template <typename V> complex& operator *=(const complex<V>& oth);
		template <typename V> complex& operator /=(const complex<V>& oth);

		template <typename V> complex operator +(const V& value) const;
		template <typename V> complex operator -(const V& value) const;
		template <typename V> complex operator *(const V& value) const;
		template <typename V> complex operator /(const V& value) const;

		template <typename V> complex& operator +=(const V& value);
		template <typename V> complex& operator -=(const V& value);
		template <typename V> complex& operator *=(const V& value);
		template <typename V> complex& operator /=(const V& value);

		T real;
		T imag;
	};

	typedef complex<float32>	complex32;
	typedef complex<float64> 	complex64;
	typedef complex<float128>	complex128;

	namespace literals
	{
		complex64 operator "" i(float128 v) { return complex64(0, v); }
		complex64 operator "" i(uint128 v) { return complex64(0, v); }
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const nm::complex<T>& value);

template <typename T, typename V> nm::complex<T> operator +(const V& value, const nm::complex<T>& c);
template <typename T, typename V> nm::complex<T> operator -(const V& value, const nm::complex<T>& c);
template <typename T, typename V> nm::complex<T> operator *(const V& value, const nm::complex<T>& c);
template <typename T, typename V> nm::complex<T> operator /(const V& value, const nm::complex<T>& c);

#include "../lib/complex.inl"