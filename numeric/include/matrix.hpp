#pragma once
#include "types.hpp"

template <typename T> std::ostream& operator <<(std::ostream& out, const nm::matr<T>& matrix);

template <typename T> nm::matr<T> operator -(const nm::matr<T>& m);

template <typename T, typename C> nm::matr<T> operator *(const C& c, const nm::matr<T>& m);
template <typename T, typename C> nm::matr<T> operator *(const nm::matr<T>& m, const C& c);
template <typename T, typename C> nm::matr<T>& operator *=(nm::matr<T>& m, const C& c);

template <typename T, typename C> nm::matr<T> operator /(const C& c, const nm::matr<T>& m);
template <typename T, typename C> nm::matr<T> operator /(const nm::matr<T>& m, const C& c);
template <typename T, typename C> nm::matr<T>& operator /=(nm::matr<T>& m, const C& c);

template <typename T, typename C> nm::matr<T> operator +(const C& c, const nm::matr<T>& m);
template <typename T, typename C> nm::matr<T> operator +(const nm::matr<T>& m, const C& c);
template <typename T, typename C> nm::matr<T> operator +(const nm::matr<T>& m, const nm::matr<C>& v);
template <typename T, typename C> nm::matr<T>& operator +=(nm::matr<T>& m, const C& c);
template <typename T, typename C> nm::matr<T>& operator +=(nm::matr<T>& m, const nm::matr<C>& v);

template <typename T, typename C> nm::matr<T> operator -(const C& c, const nm::matr<T>& m);
template <typename T, typename C> nm::matr<T> operator -(const nm::matr<T>& m, const C& c);
template <typename T, typename C> nm::matr<T> operator -(const nm::matr<T>& m, const nm::matr<C>& v);
template <typename T, typename C> nm::matr<T>& operator -=(nm::matr<T>& m, const C& c);
template <typename T, typename C> nm::matr<T>& operator -=(nm::matr<T>& m, const nm::matr<C>& v);

template <typename T, typename C> nm::matr<nm::complex<C>> operator *(nm::complex<C> c, const nm::matr<T>& m);
template <typename T, typename C> nm::matr<nm::complex<C>> operator *(const nm::matr<T>& m, nm::complex<C> c);
template <typename T, typename C> nm::matr<nm::complex<C>> operator /(nm::complex<C> c, const nm::matr<T>& m);
template <typename T, typename C> nm::matr<nm::complex<C>> operator /(const nm::matr<T>& m, nm::complex<C> c);

template <typename T, typename C> nm::matr<nm::complex<C>> operator +(nm::complex<C> c, const nm::matr<T>& m);
template <typename T, typename C> nm::matr<nm::complex<C>> operator +(const nm::matr<T>& m, nm::complex<C> c);
template <typename T, typename C> nm::matr<nm::complex<C>> operator -(nm::complex<C> c, const nm::matr<T>& m);
template <typename T, typename C> nm::matr<nm::complex<C>> operator -(const nm::matr<T>& m, nm::complex<C> c);

template <typename T, typename C> nm::matr<nm::complex<C>> operator +(const nm::matr<T>& m, const nm::matr<nm::complex<C>>& v);
template <typename T, typename C> nm::matr<nm::complex<C>> operator -(const nm::matr<T>& m, const nm::matr<nm::complex<C>>& v);

namespace nm
{
	template <typename T> matr<T>& foreach(matr<T>& matrix, op operation);								// for unary operations (neg)
	template <typename T, typename C> matr<T>& foreach(matr<T>& matrix, const C& value, op operation);	// for binary operations
}

#include "../lib/matrix.inl"