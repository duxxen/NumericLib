#pragma once
#include "types.hpp"

template <typename T> std::ostream& operator<<(std::ostream& out, const numeric::vect<T>& vector);

namespace numeric
{
	template <typename T> T dot(const vect<T>& a, const vect<T>& b);
	template <typename T> vect<T> cross(const vect<T>& a, const vect<T>& b);

	template <typename T> vect<T> operator*(T a, const vect<T>& b);
	template <typename T> vect<T> operator*(const vect<T>& a, T b);
	template <typename T> vect<T>& operator*=(vect<T>& a, T b);
	

	template <typename T> vect<T> operator/(T a, const vect<T>& b);
	template <typename T> vect<T> operator/(const vect<T>& a, T b);
	template <typename T> vect<T>& operator/=(vect<T>& a, T b);

	template <typename T> vect<T> operator+(T a, const vect<T>& b);
	template <typename T> vect<T> operator+(const vect<T>& a, T b);
	template <typename T> vect<T> operator+(const vect<T>& a, const vect<T>& b);
	template <typename T> vect<T>& operator+=(vect<T>& a, T b);
	template <typename T> vect<T>& operator+=(vect<T>& a, const vect<T>& b);
							  
	template <typename T> vect<T> operator-(const vect<T>& a);
	template <typename T> vect<T> operator-(T a, const vect<T>& b);
	template <typename T> vect<T> operator-(const vect<T>& a, T b);
	template <typename T> vect<T> operator-(const vect<T>& a, const vect<T>& b);
	template <typename T> vect<T>& operator-=(vect<T>& a, T b);
	template <typename T> vect<T>& operator-=(vect<T>& a, const vect<T>& b);
							  
	template <typename T> vect<T> foreach(const vect<T>& vector, op operation);				// for unary operations (neg)
	template <typename T> vect<T> foreach(const vect<T>& vector, T value, op operation);	// for binary operations
}

#include "../lib/vector.inl"