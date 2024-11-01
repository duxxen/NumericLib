#include "../include/types.hpp"

// --------------------------------------------------------------- I/O FUNCTIONS

template<typename T>
std::ostream& operator<<(std::ostream& out, const numeric::vect<T>& vector)
{
	for (auto& v : vector)
		out << v << "\n";
	return out;
}

// --------------------------------------------------------------- UNARY OPERATIONS

template <typename T> numeric::vect<T> operator-(const numeric::vect<T>& a) { return numeric::foreach(a, numeric::op::neg); }

namespace numeric
{
	// --------------------------------------------------------------- DOT/CROSS PRODUCTION

	template <typename T>
	T dot(const vect<T>& a, const vect<T>& b)
	{
		assert(a.size() == b.size());
		T product = NULL;
		for (int i = 0; i < a.size(); i++)
			product += a[i] * b[i];
		return product;
	}

	template <typename T>
	vect<T> cross(const vect<T>& a, const vect<T>& b)
	{
		assert(a.size() == b.size());
		assert(a.size() == 3);
		return vect<T>({
			a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0]
		});
	}

	// --------------------------------------------------------------- MULTIPLICATION

	template <typename T> vect<T> operator*(T a, const vect<T>& b) { return foreach(b, a, op::mult); }
	template <typename T> vect<T> operator*(const vect<T>& a, T b) { return foreach(a, b, op::mult); }

	template <typename T>
	vect<T>& operator*=(vect<T>& a, T b)
	{
		for (auto& v : a)
			v *= b;
		return a;
	}

	// --------------------------------------------------------------- DIVISION

	template <typename T> vect<T> operator/(T a, const vect<T>& b) { return foreach(b, a, op::div); }
	template <typename T> vect<T> operator/(const vect<T>& a, T b) { return foreach(a, b, op::div); }

	template <typename T>
	vect<T>& operator/=(vect<T>& a, T b)
	{
		for (auto& v : a)
			v /= b;
		return a;
	}

	// --------------------------------------------------------------- ADDICTION

	template <typename T> vect<T> operator+(T a, const vect<T>& b) { return foreach(b, a, op::add); }
	template <typename T> vect<T> operator+(const vect<T>& a, T b) { return foreach(a, b, op::add); }

	template <typename T>
	vect<T> operator+(const vect<T>& a, const vect<T>& b)
	{
		assert(a.size() == b.size());
		vect<T> product(a);
		for (int i = 0; i < a.size(); i++)
			product[i] += b[i];
		return product;
	}

	template <typename T>
	vect<T>& operator+=(vect<T>& a, T b)
	{
		for (auto& v : a)
			v += b;
		return a;
	}

	template <typename T>
	vect<T>& operator+=(vect<T>& a, const vect<T>& b)
	{
		assert(a.size() == b.size());
		for (int i = 0; i < a.size(); i++)
			a[i] += b[i];
		return a;
	}

	// --------------------------------------------------------------- SUBSTRACTION

	template <typename T> vect<T> operator-(T a, const vect<T>& b) { return foreach(b, a, op::sub); }
	template <typename T> vect<T> operator-(const vect<T>& a, T b) { return foreach(a, b, op::sub); }

	template <typename T>
	vect<T> operator-(const vect<T>& a, const vect<T>& b)
	{
		assert(a.size() == b.size());
		vect<T> product(a);
		for (int i = 0; i < a.size(); i++)
			product[i] -= b[i];
		return product;
	}

	template <typename T>
	vect<T>& operator-=(vect<T>& a, T b)
	{
		for (auto& v : a)
			v -= b;
		return a;
	}

	template <typename T>
	vect<T>& operator-=(vect<T>& a, const vect<T>& b)
	{
		assert(a.size() == b.size());
		for (int i = 0; i < a.size(); i++)
			a[i] -= b[i];
		return a;
	}

	// --------------------------------------------------------------- FUNCTIONS

	template<typename T>
	vect<T> foreach(const vect<T>& vector, op operation)
	{
		vect<T> product(vector);
		switch (operation)
		{
		case numeric::op::neg:
			for (auto& v : product)
				v = -v;
			break;
		case numeric::op::add:
		case numeric::op::sub:
		case numeric::op::mult:
		case numeric::op::div:
			throw std::exception("non unary operation!");
			break;
		case numeric::op::pow:
		case numeric::op::root:
			throw std::exception("missing argument!");
			break;
		default:
			throw std::exception("bad operation!");
			break;
		}
		return product;
	}

	template <typename T>
	vect<T> foreach(const vect<T>& vector, T value, op operation)
	{
		T temp = NULL;
		vect<T> product(vector);
		switch (operation)
		{
		case numeric::op::neg:
			throw std::exception("non binary operation!");
			break;
		case numeric::op::add:
			for (auto& v : product)
				v += value;
			break;
		case numeric::op::sub:
			for (auto& v : product)
				v -= value;
			break;
		case numeric::op::mult:
			for (auto& v : product)
				v *= value;
			break;
		case numeric::op::div:
			for (auto& v : product)
				v /= value;
			break;
		case numeric::op::pow:
			for (auto& v : product)
				v = pow(v, value);
			break;
		case numeric::op::root:
			temp = 1 / value;
			for (auto& v : product)
				v = pow(v, temp);
			break;
		default:
			throw std::exception("bad operation!");
			break;
		}
		return product;
	}
}