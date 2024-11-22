#pragma once
#include "complex.hpp"

namespace nm
{
	namespace tybase
	{
		template<typename T>
		inline complex_base<T>::complex_base(const T& re, const T& im) :
			real(re),
			imag(im)
		{
		}

		template<typename T>
		inline T complex_base<T>::abs() const
		{
			return nm::abs(*this);
		}

		template<typename T>
		inline T complex_base<T>::arg() const
		{
			return nm::arg(*this);
		}

		template<typename T>
		inline complex_base<T> complex_base<T>::inversed() const
		{
			T qsum = real * real + imag * imag;
			return complex_base<T>(
				real / qsum,
				-imag / qsum
			);
		}

		template<typename T>
		inline complex_base<T> complex_base<T>::conjugate() const
		{
			return complex_base(
				real,
				-imag
			);
		}
	}

	template<typename T>
	T abs(tybase::complex_base<T> value)
	{
		return sqrt(
			value.real * value.real + 
			value.imag * value.imag
		);
	}

	template<typename T>
	T arg(tybase::complex_base<T> value)
	{
		auto phi = atan(value.imag / value.real);
		if (value.real > 0)      return phi;
		else if (value.real < 0) return value.imag < 0 ? -M_PI + phi : M_PI + phi;
		else                     return value.imag < 0 ? -M_PI_2 : M_PI_2;
	}
}

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const nm::tybase::complex_base<T>& value)
{
	out << value.real;
	if (value.imag >= 0)
		out << '+';
	out << value.imag << 'i';
	return out;
}

template<typename T>
inline nm::tybase::complex_base<T> nm::tybase::complex_base<T>::operator-() const
{
	return complex_base(
		-real,
		-imag
	);
}

template<typename T>
template<typename V>
inline nm::tybase::complex_base<T>::complex_base(const complex_base<V>& oth) :
	real(oth.real),
	imag(oth.imag)
{
}

template <typename T>
template <typename V>
inline auto nm::tybase::complex_base<T>::operator +(const nm::tybase::complex_base<V>& oth) const
{
	return tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real + oth.real,
		imag + oth.imag
	);
}

template <typename T>
template <typename V>
inline auto nm::tybase::complex_base<T>::operator -(const nm::tybase::complex_base<V>& oth) const
{
	return tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real - oth.real,
		imag - oth.imag
	);;
}

template <typename T>
template <typename V>
inline auto nm::tybase::complex_base<T>::operator *(const nm::tybase::complex_base<V>& oth) const
{
	return tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real * oth.real - imag * oth.imag,
		real * oth.imag + imag * oth.real
	);
}

template <typename T>
template <typename V>
inline auto nm::tybase::complex_base<T>::operator /(const nm::tybase::complex_base<V>& oth) const
{
	auto abs = oth.real * oth.real + oth.imag * oth.imag;
	return tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		(real * oth.real + imag * oth.imag) / abs,
		(imag * oth.real - real * oth.imag) / abs
	);
}

template <typename T>
template <typename V>
inline nm::tybase::complex_base<T>& nm::tybase::complex_base<T>::operator +=(const nm::tybase::complex_base<V>& oth)
{
	real += oth.real;
	imag += oth.imag;
	return *this;
}

template <typename T>
template <typename V>
inline nm::tybase::complex_base<T>& nm::tybase::complex_base<T>::operator -=(const nm::tybase::complex_base<V>& oth)
{
	real -= oth.real;
	imag -= oth.imag;
	return *this;
}

template <typename T>
template <typename V>
inline nm::tybase::complex_base<T>& nm::tybase::complex_base<T>::operator *=(const nm::tybase::complex_base<V>& oth)
{
	auto re = real * oth.real - imag * oth.imag;
	auto im = real * oth.imag + imag * oth.real;
	real = re;
	imag = im;
	return *this;
}

template <typename T>
template <typename V>
inline nm::tybase::complex_base<T>& nm::tybase::complex_base<T>::operator /=(const nm::tybase::complex_base<V>& oth)
{
	auto abs = oth.real * oth.real + oth.imag * oth.imag;
	auto re = (real * oth.real + imag * oth.imag) / abs;
	auto im = (imag * oth.real - real * oth.imag) / abs;
	real = re;
	imag = im;
	return *this;
}

template<typename T>
template<typename V>
inline auto nm::tybase::complex_base<T>::operator +(const V& value) const
{
	return tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real + value,
		imag
	);
}

template<typename T>
template<typename V>
inline auto nm::tybase::complex_base<T>::operator -(const V& value) const
{
	return tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real - value,
		imag
	);
}

template<typename T>
template<typename V>
inline auto nm::tybase::complex_base<T>::operator *(const V& value) const
{
	return tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real * value,
		imag * value
	);
}

template<typename T>
template<typename V>
inline auto nm::tybase::complex_base<T>::operator /(const V& value) const
{
	return tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real / value,
		imag / value
	);
}

template<typename T>
template<typename V>
inline nm::tybase::complex_base<T>& nm::tybase::complex_base<T>::operator +=(const V& value)
{
	real += value;
	return *this;
}

template<typename T>
template<typename V>
inline nm::tybase::complex_base<T>& nm::tybase::complex_base<T>::operator -=(const V& value)
{
	real -= value;
	return *this;
}

template<typename T>
template<typename V>
inline nm::tybase::complex_base<T>& nm::tybase::complex_base<T>::operator *=(const V& value)
{
	real *= value;
	imag *= value;
	return *this;
}

template<typename T>
template<typename V>
inline nm::tybase::complex_base<T>& nm::tybase::complex_base<T>::operator /=(const V& value)
{
	real /= value;
	imag /= value;
	return *this;
}

template<typename T>
template<typename V>
inline bool nm::tybase::complex_base<T>::operator==(const complex_base<V>& oth) const
{
	return real == oth.real
		&& imag == oth.imag;
}

template<typename T>
template<typename V>
inline bool nm::tybase::complex_base<T>::operator!=(const complex_base<V>& oth) const
{
	return real != oth.real
		|| imag != oth.imag;
}

template<typename T>
template<typename V>
inline bool nm::tybase::complex_base<T>::operator==(const V& value) const
{
	return abs() == value;
}

template<typename T>
template<typename V>
inline bool nm::tybase::complex_base<T>::operator!=(const V& value) const
{
	return abs() != value;
}

template<typename T, typename V>
inline auto operator+(const V& value, const nm::tybase::complex_base<T>& c)
{
	return nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, nm::tybase::complex_base<T>, nm::tybase::complex_base<V>>(
		value + c.real,
		c.imag
	);
}

template <typename T, typename V>
inline auto operator -(const V& value, const nm::tybase::complex_base<T>& c)
{
	return nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, nm::tybase::complex_base<T>, nm::tybase::complex_base<V>>(
		value - c.real,
		-c.imag
	);
}

template <typename T, typename V>
inline auto operator *(const V& value, const nm::tybase::complex_base<T>& c)
{
	return nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, nm::tybase::complex_base<T>, nm::tybase::complex_base<V>>(
		c.real * value,
		c.imag * value
	);
}

template <typename T, typename V>
inline auto operator /(const V& value, const nm::tybase::complex_base<T>& c)
{
	auto inv = c.inverse();
	return nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, nm::tybase::complex_base<T>, nm::tybase::complex_base<V>>(
		inv.real * value,
		inv.imag * value
	);
}