#include "../include/complex.hpp"

template<typename T>
inline nm::complex<T>::complex(const T& re, const T& im) : 
	real(re),
	imag(im)
{
}

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const nm::complex<T>& value)
{
	out << value.real;
	if (value.imag >= 0)
		out << '+';
	out << value.imag << 'i';
	return out;
}

template<typename T>
inline nm::complex<T> nm::complex<T>::operator-() const
{
	return complex(
		-real, 
		-imag
	);
}

template <typename T> 
template <typename V> 
inline nm::complex<T> nm::complex<T>::operator +(const nm::complex<V>& oth) const
{ 
	return complex(
		real + oth.real, 
		imag + oth.imag
	); 
}

template <typename T> 
template <typename V> 
inline nm::complex<T> nm::complex<T>::operator -(const nm::complex<V>& oth) const 
{ 
	return complex(
		real - oth.real,
		imag - oth.imag
	);
}

template <typename T> 
template <typename V> 
inline nm::complex<T> nm::complex<T>::operator *(const nm::complex<V>& oth) const 
{
	return complex(
		real * oth.real - imag * oth.imag,
		real * oth.imag + imag * oth.real
	);
}

template <typename T> 
template <typename V> 
inline nm::complex<T> nm::complex<T>::operator /(const nm::complex<V>& oth) const 
{
	auto abs = oth.real * oth.real + oth.imag * oth.imag;
	return complex(
		(real * oth.real + imag * oth.imag) / abs,
		(imag * oth.real - real * oth.imag) / abs
	);
}
				   							
template <typename T> 
template <typename V> 
inline nm::complex<T>& nm::complex<T>::operator +=(const nm::complex<V>& oth)
{
	real += oth.real;
	imag += oth.imag;
	return *this;
}

template <typename T> 
template <typename V> 
inline nm::complex<T>& nm::complex<T>::operator -=(const nm::complex<V>& oth) 
{
	real -= oth.real;
	imag -= oth.imag;
	return *this;
}

template <typename T> 
template <typename V> 
inline nm::complex<T>& nm::complex<T>::operator *=(const nm::complex<V>& oth)
{
	auto re = real * oth.real - imag * oth.imag;
	auto im = real * oth.imag + imag * oth.real;
	real = re;
	imag = im;
	return *this;
}

template <typename T>
template <typename V> 
inline nm::complex<T>& nm::complex<T>::operator /=(const nm::complex<V>& oth)
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
inline nm::complex<T> nm::complex<T>::operator +(const V& value) const
{
	return complex(
		real + value, 
		imag
	);
}

template<typename T>
template<typename V>
inline nm::complex<T> nm::complex<T>::operator -(const V& value) const
{
	return complex(
		real - value, 
		imag
	);
}

template<typename T>
template<typename V>
inline nm::complex<T> nm::complex<T>::operator *(const V& value) const
{
	return complex(
		real * value, 
		imag * value
	);
}

template<typename T>
template<typename V>
inline nm::complex<T> nm::complex<T>::operator /(const V& value) const
{
	return complex(
		real * value,
		imag * value
	);
}

template<typename T>
template<typename V>
inline nm::complex<T>& nm::complex<T>::operator +=(const V& value)
{
	real += value;
	return *this;
}

template<typename T>
template<typename V>
inline nm::complex<T>& nm::complex<T>::operator -=(const V& value)
{
	real -= value;
	return *this;
}

template<typename T>
template<typename V>
inline nm::complex<T>& nm::complex<T>::operator *=(const V& value)
{
	real *= value;
	imag *= value;
	return *this;
}

template<typename T>
template<typename V>
inline nm::complex<T>& nm::complex<T>::operator /=(const V& value)
{
	real /= value;
	imag /= value;
	return *this;
}

template <typename T, typename V> 
nm::complex<T> operator +(const V& value, const nm::complex<T>& c)
{
	return nm::complex(
		c.real + value, 
		c.imag
	);
}

template <typename T, typename V>
nm::complex<T> operator -(const V& value, const nm::complex<T>& c)
{
	return nm::complex(
		c.real - value, 
		c.imag
	);
}

template <typename T, typename V>
nm::complex<T> operator *(const V& value, const nm::complex<T>& c)
{
	return nm::complex(
		c.real * value, 
		c.imag * value
	);
}

template <typename T, typename V>
nm::complex<T> operator /(const V& value, const nm::complex<T>& c)
{
	return nm::complex(
		c.real / value,
		c.imag / value
	);
}
