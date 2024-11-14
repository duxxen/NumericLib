#include "../include/complex.hpp"

namespace nm
{
	namespace base_type
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
			return sqrt(real * real + imag * imag);
		}

		template<typename T>
		inline T complex_base<T>::arg() const
		{
			return acos(real / abs());
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
		inline complex_base<T> complex_base<T>::conjugated() const
		{
			return complex_base(
				real,
				-imag
			);
		}
	}
}

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const nm::base_type::complex_base<T>& value)
{
	out << value.real;
	if (value.imag >= 0)
		out << '+';
	out << value.imag << 'i';
	return out;
}

template<typename T>
inline nm::base_type::complex_base<T> nm::base_type::complex_base<T>::operator-() const
{
	return complex_base(
		-real, 
		-imag
	);
}

template<typename T>
template<typename V>
inline nm::base_type::complex_base<T>::complex_base(const complex_base<V>& oth) :
	real(oth.real),
	imag(oth.imag)
{
}

template <typename T>
template <typename V> 
inline auto nm::base_type::complex_base<T>::operator +(const nm::base_type::complex_base<V>& oth) const
{ 
	return typing::conditional_t<typing::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real + oth.real,
		imag + oth.imag
	);
}

template <typename T> 
template <typename V> 
inline auto nm::base_type::complex_base<T>::operator -(const nm::base_type::complex_base<V>& oth) const 
{ 
	return typing::conditional_t<typing::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real - oth.real,
		imag - oth.imag
	);;
}

template <typename T> 
template <typename V> 
inline auto nm::base_type::complex_base<T>::operator *(const nm::base_type::complex_base<V>& oth) const 
{
	return typing::conditional_t<typing::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real * oth.real - imag * oth.imag,
		real * oth.imag + imag * oth.real
	);
}

template <typename T> 
template <typename V> 
inline auto nm::base_type::complex_base<T>::operator /(const nm::base_type::complex_base<V>& oth) const 
{
	auto abs = oth.real * oth.real + oth.imag * oth.imag;
	return typing::conditional_t<typing::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		(real * oth.real + imag * oth.imag) / abs,
		(imag * oth.real - real * oth.imag) / abs
	);
}
				   							
template <typename T> 
template <typename V> 
inline nm::base_type::complex_base<T>& nm::base_type::complex_base<T>::operator +=(const nm::base_type::complex_base<V>& oth)
{
	real += oth.real;
	imag += oth.imag;
	return *this;
}

template <typename T> 
template <typename V> 
inline nm::base_type::complex_base<T>& nm::base_type::complex_base<T>::operator -=(const nm::base_type::complex_base<V>& oth) 
{
	real -= oth.real;
	imag -= oth.imag;
	return *this;
}

template <typename T> 
template <typename V> 
inline nm::base_type::complex_base<T>& nm::base_type::complex_base<T>::operator *=(const nm::base_type::complex_base<V>& oth)
{
	auto re = real * oth.real - imag * oth.imag;
	auto im = real * oth.imag + imag * oth.real;
	real = re;
	imag = im;
	return *this;
}

template <typename T>
template <typename V> 
inline nm::base_type::complex_base<T>& nm::base_type::complex_base<T>::operator /=(const nm::base_type::complex_base<V>& oth)
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
inline auto nm::base_type::complex_base<T>::operator +(const V& value) const
{
	return typing::conditional_t<typing::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real + value,
		imag
	);
}

template<typename T>
template<typename V>
inline auto nm::base_type::complex_base<T>::operator -(const V& value) const
{
	return typing::conditional_t<typing::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real - value,
		imag
	);
}

template<typename T>
template<typename V>
inline auto nm::base_type::complex_base<T>::operator *(const V& value) const
{
	return typing::conditional_t<typing::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real * value,
		imag * value
	);
}

template<typename T>
template<typename V>
inline auto nm::base_type::complex_base<T>::operator /(const V& value) const
{
	return typing::conditional_t<typing::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>(
		real / value,
		imag / value
	);
}

template<typename T>
template<typename V>
inline nm::base_type::complex_base<T>& nm::base_type::complex_base<T>::operator +=(const V& value)
{
	real += value;
	return *this;
}

template<typename T>
template<typename V>
inline nm::base_type::complex_base<T>& nm::base_type::complex_base<T>::operator -=(const V& value)
{
	real -= value;
	return *this;
}

template<typename T>
template<typename V>
inline nm::base_type::complex_base<T>& nm::base_type::complex_base<T>::operator *=(const V& value)
{
	real *= value;
	imag *= value;
	return *this;
}

template<typename T>
template<typename V>
inline nm::base_type::complex_base<T>& nm::base_type::complex_base<T>::operator /=(const V& value)
{
	real /= value;
	imag /= value;
	return *this;
}

template<typename T, typename V>
inline auto operator+(const V& value, const nm::base_type::complex_base<T>& c)
{
	return nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, nm::base_type::complex_base<T>, nm::base_type::complex_base<V>>(
		value + c.real,
		c.imag
	);
}

template <typename T, typename V>
inline auto operator -(const V& value, const nm::base_type::complex_base<T>& c)
{
	return nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, nm::base_type::complex_base<T>, nm::base_type::complex_base<V>>(
		value - c.real,
		c.imag
	);
}

template <typename T, typename V>
inline auto operator *(const V& value, const nm::base_type::complex_base<T>& c)
{
	return nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, nm::base_type::complex_base<T>, nm::base_type::complex_base<V>>(
		c.real * value,
		c.imag * value
	);
}

template <typename T, typename V>
inline auto operator /(const V& value, const nm::base_type::complex_base<T>& c)
{
	auto inv = c.inverse();
	return nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, nm::base_type::complex_base<T>, nm::base_type::complex_base<V>>(
		inv.real * value,
		inv.imag * value
	);
}
