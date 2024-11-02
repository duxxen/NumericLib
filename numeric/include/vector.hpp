#pragma once
#include "types.hpp"

template <typename T> std::ostream& operator <<(std::ostream& out, const nm::vect<T>& vector);

template <typename T> nm::vect<T> operator -(const nm::vect<T>& v);

template <typename T, typename C> nm::vect<T> operator *(const C& c, const nm::vect<T>& v);
template <typename T, typename C> nm::vect<T> operator *(const nm::vect<T>& v, const C& c);
template <typename T, typename C> nm::vect<T>& operator *=(nm::vect<T>& v, const C& c);
					  
template <typename T, typename C> nm::vect<T> operator /(const C& c, const nm::vect<T>& v);
template <typename T, typename C> nm::vect<T> operator /(const nm::vect<T>& v, const C& c);
template <typename T, typename C> nm::vect<T>& operator /=(nm::vect<T>& v, const C& c);
					
template <typename T, typename C> nm::vect<T> operator +(const C& c, const nm::vect<T>& v);
template <typename T, typename C> nm::vect<T> operator +(const nm::vect<T>& v, const C& c);
template <typename T, typename C> nm::vect<T> operator +(const nm::vect<T>& v, const nm::vect<C>& m);	// need vect<complex> realisation
template <typename T, typename C> nm::vect<T>& operator +=(nm::vect<T>& v, const C& c);
template <typename T, typename C> nm::vect<T>& operator +=(nm::vect<T>& v, const nm::vect<C>& m);
					
template <typename T, typename C> nm::vect<T> operator -(const C& c, const nm::vect<T>& v);
template <typename T, typename C> nm::vect<T> operator -(const nm::vect<T>& v, const C& c);
template <typename T, typename C> nm::vect<T> operator -(const nm::vect<T>& v, const nm::vect<C>& m);	// need vect<complex> realisation
template <typename T, typename C> nm::vect<T>& operator -=(nm::vect<T>& v, const C& c);
template <typename T, typename C> nm::vect<T>& operator -=(nm::vect<T>& v, const nm::vect<C>& m);

template <typename T, typename C> nm::vect<nm::complex<C>> operator *(nm::complex<C> c, const nm::vect<T>& v);
template <typename T, typename C> nm::vect<nm::complex<C>> operator *(const nm::vect<T>& v, nm::complex<C> c);
template <typename T, typename C> nm::vect<nm::complex<C>> operator /(nm::complex<C> c, const nm::vect<T>& v);
template <typename T, typename C> nm::vect<nm::complex<C>> operator /(const nm::vect<T>& v, nm::complex<C> c);

template <typename T, typename C> nm::vect<nm::complex<C>> operator +(nm::complex<C> c, const nm::vect<T>& v);
template <typename T, typename C> nm::vect<nm::complex<C>> operator +(const nm::vect<T>& v, nm::complex<C> c);
template <typename T, typename C> nm::vect<nm::complex<C>> operator -(nm::complex<C> c, const nm::vect<T>& v);
template <typename T, typename C> nm::vect<nm::complex<C>> operator -(const nm::vect<T>& v, nm::complex<C> c);

template <typename T, typename C> nm::vect<nm::complex<C>> operator +(const nm::vect<T>& v, const nm::vect<nm::complex<C>>& m);
template <typename T, typename C> nm::vect<nm::complex<C>> operator -(const nm::vect<T>& v, const nm::vect<nm::complex<C>>& m);

namespace nm
{
	template <typename T> vect<T>& foreach(vect<T>& vector, op operation);						// for unary operations (neg)
	template <typename T, typename C> vect<T>& foreach(vect<T>& vector, const C& value, op operation);	// for binary operations
}

#include "../lib/vector.inl"
