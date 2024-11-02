#include "../include/vector.hpp"

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const nm::vect<T>& vector)
{
	for (auto& v : vector)
		out << v << "\n";
	return out;
}

template <typename T> 
nm::vect<T> operator-(const nm::vect<T>& v)
{
	auto product(v);
	return nm::foreach(v, nm::op::neg);
}

template <typename T, typename C> 
nm::vect<T> operator*(const C& c, const nm::vect<T>& v)
{
	auto product(v);
	return nm::foreach(product, c, nm::op::mult);
}

template <typename T, typename C> 
nm::vect<T> operator*(const nm::vect<T>& v, const C& c)
{
	auto product(v);
	return nm::foreach(product, c, nm::op::mult);
}

template <typename T, typename C>
nm::vect<T>& operator*=(nm::vect<T>& v, const C& c)
{
	return nm::foreach(v, c, nm::op::mult);
}

template <typename T, typename C>
nm::vect<T> operator/(const C& c, const nm::vect<T>& v)
{
	auto product(v);
	return nm::foreach(product, c, nm::op::div);
}

template <typename T, typename C>
nm::vect<T> operator/(const nm::vect<T>& v, const C& c)
{
	auto product(v);
	return nm::foreach(product, c, nm::op::div);
}

template <typename T, typename C> 
nm::vect<T>& operator/=(nm::vect<T>& v, const C& c)
{
	return nm::foreach(v, c, nm::op::div);
}

template <typename T, typename C> 
nm::vect<T> operator+(const C& c, const nm::vect<T>& v)
{
	auto product(v);
	return nm::foreach(product, c, nm::op::add);
}

template <typename T, typename C>
nm::vect<T> operator+(const nm::vect<T>& v, const C& c)
{
	auto product(v);
	return nm::foreach(product, c, nm::op::add);
}

template <typename T, typename C>
nm::vect<T> operator+(const nm::vect<T>& v, const nm::vect<C>& m)
{
	assert(v.size() == m.size());
	auto product(v);
	for (int i = 0; i < v.size(); i++)
		product[i] += m[i];
	return product;
}

template <typename T, typename C>
nm::vect<T>& operator+=(nm::vect<T>& v, const C& c)
{
	return nm::foreach(v, c, nm::op::add);
}

template <typename T, typename C> 
nm::vect<T>& operator+=(nm::vect<T>& v, const nm::vect<C>& m)
{
	assert(v.size() == m.size());
	for (int i = 0; i < v.size(); i++)
		v[i] += m[i];
	return v;
}

template <typename T, typename C> 
nm::vect<T> operator-(const C& c, const nm::vect<T>& v)
{
	auto product(v);
	return nm::foreach(product, c, nm::op::sub);
}

template <typename T, typename C>
nm::vect<T> operator-(const nm::vect<T>& v, const C& c)
{
	auto product(v);
	return nm::foreach(product, c, nm::op::sub);
}

template <typename T, typename C>
nm::vect<T> operator-(const nm::vect<T>& v, const nm::vect<T>& m)
{
	assert(v.size() == m.size());
	auto product(v);
	for (int i = 0; i < v.size(); i++)
		product[i] -= m[i];
	return product;
}

template <typename T, typename C> 
nm::vect<T>& operator-=(nm::vect<T>& v, const C& c)
{
	return nm::foreach(v, c, nm::op::sub);
}

template <typename T, typename C>
nm::vect<T>& operator-=(nm::vect<T>& v, const nm::vect<T>& m)
{
	assert(v.size() == m.size());
	for (int i = 0; i < v.size(); i++)
		v[i] -= m[i];
	return v;
}

template<typename T, typename C>
inline nm::vect<nm::complex<C>> operator*(nm::complex<C> c, const nm::vect<T>& v)
{
	nm::vect<nm::complex<C>> product(v.size(), c);
	for (int i = 0; i < v.size(); i++)
		product[i] *= v[i];
	return product;
}

template<typename T, typename C>
inline nm::vect<nm::complex<C>> operator*(const nm::vect<T>& v, nm::complex<C> c)
{
	nm::vect<nm::complex<C>> product(v.size(), c);
	for (int i = 0; i < v.size(); i++)
		product[i] *= v[i];
	return product;
}

template<typename T, typename C>
inline nm::vect<nm::complex<C>> operator/(nm::complex<C> c, const nm::vect<T>& v)
{
	nm::vect<nm::complex<C>> product(v.size(), c);
	for (int i = 0; i < v.size(); i++)
		product[i] /= v[i];
	return product;
}

template<typename T, typename C>
inline nm::vect<nm::complex<C>> operator/(const nm::vect<T>& v, nm::complex<C> c)
{
	nm::vect<nm::complex<C>> product(v.size(), c);
	for (int i = 0; i < v.size(); i++)
		product[i] /= v[i];
	return product;
}

template<typename T, typename C>
inline nm::vect<nm::complex<C>> operator+(nm::complex<C> c, const nm::vect<T>& v)
{
	nm::vect<nm::complex<C>> product(v.size(), c);
	for (int i = 0; i < v.size(); i++)
		product[i] += v[i];
	return product;
}

template<typename T, typename C>
inline nm::vect<nm::complex<C>> operator+(const nm::vect<T>& v, nm::complex<C> c)
{
	nm::vect<nm::complex<C>> product(v.size(), c);
	for (int i = 0; i < v.size(); i++)
		product[i] += v[i];
	return product;
}

template<typename T, typename C>
inline nm::vect<nm::complex<C>> operator-(nm::complex<C> c, const nm::vect<T>& v)
{
	nm::vect<nm::complex<C>> product(v.size(), c);
	for (int i = 0; i < v.size(); i++)
		product[i] -= v[i];
	return product;
}

template<typename T, typename C>
inline nm::vect<nm::complex<C>> operator-(const nm::vect<T>& v, nm::complex<C> c)
{
	nm::vect<nm::complex<C>> product(v.size(), c);
	for (int i = 0; i < v.size(); i++)
		product[i] -= v[i];
	return product;
}

template <typename T, typename C> 
nm::vect<nm::complex<C>> operator +(const nm::vect<T>& v, const nm::vect<nm::complex<C>>& m)
{
	assert(v.size() == m.size());
	auto product(m);
	for (int i = 0; i < v.size(); i++)
		product[i] += v[i];
	return product;
}

template <typename T, typename C>
nm::vect<nm::complex<C>> operator -(const nm::vect<T>& v, const nm::vect<nm::complex<C>>& m)
{
	assert(v.size() == m.size());
	auto product(m);
	for (int i = 0; i < v.size(); i++)
		product[i] -= v[i];
	return product;
}

namespace nm
{
	template <typename T>
	inline vect<T>& foreach(vect<T>& vector, op operation)
	{
		switch (operation)
		{
		case nm::op::neg:
			for (auto& v : vector)
				v = -v;
			break;
		case nm::op::sum:
		case nm::op::diff:
		case nm::op::mult:
		case nm::op::div:
			throw std::exception("non unary operation!");
			break;
		case nm::op::pow:
		case nm::op::root:
			throw std::exception("missing argument!");
			break;
		}
		return vector;
	}

	template<typename T, typename C>
	inline vect<T>& foreach(vect<T>& vector, const C& value, op operation)
	{
		switch (operation)
		{
		case nm::op::neg:
			throw std::exception("non binary operation!");
			break;
		case nm::op::sum:
			for (auto& v : vector)
				v += value;
			break;
		case nm::op::diff:
			for (auto& v : vector)
				v -= value;
			break;
		case nm::op::mult:
			for (auto& v : vector)
				v *= value;
			break;
		case nm::op::div:
			for (auto& v : vector)
				v /= value;
			break;
		case nm::op::pow:
			for (auto& v : vector)
				v = pow(v, value);
			break;
		case nm::op::root:
			auto p = 1.0 / value;
			for (auto& v : vector)
				v = pow(v, p);
			break;
		}
		return vector;
	}
}