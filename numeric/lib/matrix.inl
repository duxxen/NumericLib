#include "../include/matrix.hpp"

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const nm::matr<T>& matrix)
{
	for (auto& string : matrix)
	{
		for (auto& value : string)
		{
			out << value << " ";
		}
		out << "\n";
	}
	return out;
}

template<typename T>
inline nm::matr<T> operator-(const nm::matr<T>& m)
{
	auto product(m);
	return nm::foreach(product, nm::op::neg);
}

template<typename T, typename C>
inline nm::matr<T> operator*(const C& c, const nm::matr<T>& m)
{
	auto product(m);
	return nm::foreach(product, c, nm::op::mult);
}

template<typename T, typename C>
inline nm::matr<T> operator*(const nm::matr<T>& m, const C& c)
{
	auto product(m);
	return nm::foreach(product, c, nm::op::mult);
}

template<typename T, typename C>
inline nm::matr<T>& operator*=(nm::matr<T>& m, const C& c)
{
	return nm::foreach(m, c, nm::op::mult);
}

template<typename T, typename C>
inline nm::matr<T> operator/(const C& c, const nm::matr<T>& m)
{
	auto product(m);
	return nm::foreach(product, c, nm::op::div);
}

template<typename T, typename C>
inline nm::matr<T> operator/(const nm::matr<T>& m, const C& c)
{
	auto product(m);
	return nm::foreach(product, c, nm::op::div);
}

template<typename T, typename C>
inline nm::matr<T>& operator/=(nm::matr<T>& m, const C& c)
{
	return nm::foreach(m, c, nm::op::div);
}

template<typename T, typename C>
inline nm::matr<T> operator+(const C& c, const nm::matr<T>& m)
{
	auto product(m);
	return nm::foreach(product, c, nm::op::sum);
}

template<typename T, typename C>
inline nm::matr<T> operator+(const nm::matr<T>& m, const C& c)
{
	auto product(m);
	return nm::foreach(product, c, nm::op::sum);
}

template<typename T, typename C>
inline nm::matr<T> operator+(const nm::matr<T>& m, const nm::matr<C>& v)
{
	assert(m.size() == v.size());
	auto product(m);
	for (int i = 0; i < m.size(); i++)
		product[i] += v[i];
	return product;
}

template<typename T, typename C>
inline nm::matr<T>& operator+=(nm::matr<T>& m, const C& c)
{
	auto product(m);
	return nm::foreach(product, c, nm::op::sum);
}

template<typename T, typename C>
inline nm::matr<T>& operator+=(nm::matr<T>& m, const nm::matr<C>& v)
{
	assert(m.size() == v.size());
	for (int i = 0; i < m.size(); i++)
		m[i] += v[i];
	return m;
}

template<typename T, typename C>
inline nm::matr<T> operator-(const C& c, const nm::matr<T>& m)
{
	auto product(m);
	return nm::foreach(product, c, nm::op::diff);
}

template<typename T, typename C>
inline nm::matr<T> operator-(const nm::matr<T>& m, const C& c)
{
	auto product(m);
	return nm::foreach(product, c, nm::op::diff);
}

template<typename T, typename C>
inline nm::matr<T> operator-(const nm::matr<T>& m, const nm::matr<C>& v)
{
	assert(m.size() == v.size());
	auto product(m);
	for (int i = 0; i < m.size(); i++)
		product[i] -= v[i];
	return product;
}

template<typename T, typename C>
inline nm::matr<T>& operator-=(nm::matr<T>& m, const C& c)
{
	return nm::foreach(m, c, nm::op::diff);
}

template<typename T, typename C>
inline nm::matr<T>& operator-=(nm::matr<T>& m, const nm::matr<C>& v)
{
	assert(m.size() == v.size());
	for (int i = 0; i < m.size(); i++)
		m[i] += v[i];
	return m;
}

template<typename T, typename C>
inline nm::matr<nm::complex<C>> operator*(nm::complex<C> c, const nm::matr<T>& m)
{
	nm::matr<nm::complex<C>> product(m.size(), nm::vect(m.front().size(), c));
	for (int i = 0; i < m.size(); i++)
		product[i] *= m[i];
	return product;
}

template<typename T, typename C>
inline nm::matr<nm::complex<C>> operator*(const nm::matr<T>& m, nm::complex<C> c)
{
	nm::matr<nm::complex<C>> product(m.size(), nm::vect(m.front().size(), c));
	for (int i = 0; i < m.size(); i++)
		product[i] *= m[i];
	return product;
}

template<typename T, typename C>
inline nm::matr<nm::complex<C>> operator/(nm::complex<C> c, const nm::matr<T>& m)
{
	nm::matr<nm::complex<C>> product(m.size(), nm::vect(m.front().size(), c));
	for (int i = 0; i < m.size(); i++)
		product[i] /= m[i];
	return product;
}

template<typename T, typename C>
inline nm::matr<nm::complex<C>> operator/(const nm::matr<T>& m, nm::complex<C> c)
{
	nm::matr<nm::complex<C>> product(m.size(), nm::vect<nm::complex<C>>(m.front().size()));
	for (int i = 0; i < m.size(); i++)
		product[i] = m[i] / c;
	return product;
}

template<typename T, typename C>
inline nm::matr<nm::complex<C>> operator+(nm::complex<C> c, const nm::matr<T>& m)
{
	nm::matr<nm::complex<C>> product(m.size(), nm::vect(m.front().size(), c));
	for (int i = 0; i < m.size(); i++)
		product[i] += m[i];
	return product;
}

template<typename T, typename C>
inline nm::matr<nm::complex<C>> operator+(const nm::matr<T>& m, nm::complex<C> c)
{
	nm::matr<nm::complex<C>> product(m.size(), nm::vect(m.front().size(), c));
	for (int i = 0; i < m.size(); i++)
		product[i] += m[i];
	return product;
}

template<typename T, typename C>
inline nm::matr<nm::complex<C>> operator-(nm::complex<C> c, const nm::matr<T>& m)
{
	nm::matr<nm::complex<C>> product(m.size(), nm::vect(m.front().size(), c));
	for (int i = 0; i < m.size(); i++)
		product[i] -= m[i];
	return product;
}

template<typename T, typename C>
inline nm::matr<nm::complex<C>> operator-(const nm::matr<T>& m, nm::complex<C> c)
{
	nm::matr<nm::complex<C>> product(m.size(), nm::vect(m.front().size(), c));
	for (int i = 0; i < m.size(); i++)
		product[i] -= m[i];
	return product;
}

template <typename T, typename C> 
nm::matr<nm::complex<C>> operator +(const nm::matr<T>& m, const nm::matr<nm::complex<C>>& v)
{
	auto product(v);
	for (int i = 0; i < m.size(); i++)
		product[i] += m[i];
	return product;
}

template <typename T, typename C> 
nm::matr<nm::complex<C>> operator -(const nm::matr<T>& m, const nm::matr<nm::complex<C>>& v)
{
	auto product(v);
	for (int i = 0; i < m.size(); i++)
		product[i] -= m[i];
	return product;
}

namespace nm
{
	template <typename T>
	matr<T>& foreach(matr<T>& matrix, op operation)
	{
		for (auto& string : matrix)
			foreach(string, operation);
		return matrix;
	}

	template <typename T, typename C>
	matr<T>& foreach(matr<T>& matrix, const C& value, op operation)
	{
		for (auto& string : matrix)
			foreach(string, operation);
		return matrix;
	}
}