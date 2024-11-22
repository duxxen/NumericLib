#pragma once
#include "vector.hpp"
#include "../linalg/operations.hpp"

namespace nm
{
	namespace tybase
	{
		template<typename T>
		inline vector_base<T>::vector_base(size1D_t n) :
			base(n)
		{
		}

		template<typename T>
		inline vector_base<T>::vector_base(size1D_t n, const T& value) :
			base(n, value)
		{
		}

		template<typename T>
		inline vector_base<T>::vector_base(const std::vector<T>& stdvect) :
			base(stdvect)
		{
		}

		template<typename T>
		inline vector_base<T>::vector_base(const std::initializer_list<T>& rawvect) :
			base(rawvect)
		{
		}

		template<typename T>
		inline void vector_base<T>::fill(T value)
		{
			for (auto& elem : base)
				elem = value;
		}

		template<typename T>
		inline std::vector<T>& vector_base<T>::stdvect()
		{
			return base;
		}

		template<typename T>
		inline const std::vector<T>& vector_base<T>::stdvect() const
		{
			return base;
		}

		template<typename T>
		inline size1D_t vector_base<T>::size() const
		{
			return base.size();
		}

		template<typename T>
		inline T& vector_base<T>::operator[](int128_t i)
		{
			return i < 0 ? base[size() + i] : base[i];
		}

		template<typename T>
		inline T& vector_base<T>::operator()(int128_t i)
		{
			return (*this)[i];
		}

		template<typename T>
		inline const T& vector_base<T>::operator[](int128_t i) const
		{
			return i < 0 ? base[size() + i] : base[i];
		}

		template<typename T>
		inline const T& vector_base<T>::operator()(int128_t i) const
		{
			return (*this)[i];
		}

		template<typename T>
		inline vector_base<T> vector_base<T>::slice(int128_t beg, int128_t end, int128_t step) const
		{
			auto n = 1 + std::abs(end - beg) / step;
			if (beg > end)
				step = -step;
			vector_base<T> result(n);
			for (int i = 0; i < n; i++)
				result[i] = (*this)[beg + i * step];
			return result;
		}

		template<typename T>
		inline auto vector_base<T>::begin()
		{
			return base.begin();
		}

		template<typename T>
		inline auto vector_base<T>::begin() const
		{
			return base.begin();
		}

		template<typename T>
		inline auto vector_base<T>::end()
		{
			return base.end();
		}

		template<typename T>
		inline auto vector_base<T>::end() const
		{
			return base.end();
		}

		template<typename T>
		inline void vector_base<T>::sort(bool ascend)
		{
			auto pred = ascend ?
				[](T a, T b) -> bool { return a < b; }
				:
				[](T a, T b) -> bool { return a > b; };

			std::stable_sort(base.begin(), base.end(), pred);
		}

		template<typename T>
		inline vector_base<T> vector_base<T>::sorted(bool ascend) const
		{
			vector_base<T> result(base);
			auto pred = ascend ?
				[](T a, T b) -> bool { return a < b; }
				:
				[](T a, T b) -> bool { return a > b; };

			std::stable_sort(result.base.begin(), result.base.end(), pred);
			return result;
		}

		template<typename T>
		inline T vector_base<T>::max() const
		{
			return base[argmax()];
		}

		template<typename T>
		inline T vector_base<T>::min() const
		{
			return base[argmin()];
		}

		template<typename T>
		inline std::pair<T, T> vector_base<T>::minmax() const
		{
			return std::make_pair(min(), max());
		}

		template<typename T>
		inline size1D_t vector_base<T>::argmax() const
		{
			return std::distance(base.begin(), std::max_element(base.begin(), base.end()));
		}

		template<typename T>
		inline size1D_t vector_base<T>::argmin() const
		{
			return std::distance(base.begin(), std::min_element(base.begin(), base.end()));
		}

		template<typename T>
		inline size2D_t vector_base<T>::argminmax() const
		{
			return size2D_t(argmin(), argmax());
		}

		template<typename T>
		inline void vector_base<T>::normalize()
		{
			auto len = norm2();
			for (auto& elem : base)
				elem /= len;
		}

		template<typename T>
		inline vector_base<T> vector_base<T>::normalized() const
		{
			vector_base<T> result(base);
			result.normalize();
			return result;
		}

		template<typename T>
		inline auto vector_base<T>::abs() const
		{
			return norm2();
		}

		template<typename T>
		inline auto vector_base<T>::norm1() const
		{
			T sumv = 0;
			for (auto& elem : base)
				sumv += nm::abs(elem);
			return sumv;
		}

		template<typename T>
		inline auto vector_base<T>::norm2() const
		{
			using RT = tycomp::inner_switch<tycomp::is_complex<T>::value, T>::inner;
			RT sumv = 0;
			for (auto& elem : base)
				sumv += nm::pow(nm::abs(elem), 2);
			return nm::sqrt(sumv);
		}

		template<typename T>
		inline auto vector_base<T>::normi() const
		{
			T amax = nm::abs(base[0]);
			for (auto& elem : base)
				amax = nm::abs(elem);
			return amax;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::dot(const vector_base<V>& oth) const
		{
			return nm::dot(*this, oth);
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::dot(const matrix_base<V>& mat) const
		{
			return nm::dot(*this, mat);
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::cross(const vector_base<V>& oth) const
		{
			return nm::cross(*this, oth);
		}

		template<typename T>
		inline vector_base<T> vector_base<T>::operator-() const
		{
			vector_base<T> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = -base[i];
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator+(const V& val) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;

			vector_base<RT> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] + val;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator-(const V& val) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;

			vector_base<RT> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] - val;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator*(const V& val) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;

			vector_base<RT> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] * val;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator/(const V& val) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;

			vector_base<RT> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] / val;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator+(const complex_base<V>& cmp) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>;

			vector_base<RT> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] + cmp;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator-(const complex_base<V>& cmp) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>;

			vector_base<RT> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] - cmp;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator*(const complex_base<V>& cmp) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>;

			vector_base<RT> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] * cmp;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator/(const complex_base<V>& cmp) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>;

			vector_base<RT> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] / cmp;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator+(const vector_base<V>& oth) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;
			assert(size() == oth.size());

			vector_base<RT> result(base.size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] + oth[i];
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator-(const vector_base<V>& oth) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;
			assert(size() == oth.size());

			vector_base<RT> result(base.size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] - oth[i];
			return result;
		}

		template<typename T>
		inline void vector_base<T>::operator+=(const T& value)
		{
			for (auto& elem : base)
				elem += value;
		}

		template<typename T>
		inline void vector_base<T>::operator-=(const T& value)
		{
			for (auto& elem : base)
				elem -= value;
		}

		template<typename T>
		inline void vector_base<T>::operator*=(const T& value)
		{
			for (auto& elem : base)
				elem *= value;
		}

		template<typename T>
		inline void vector_base<T>::operator/=(const T& value)
		{
			for (auto& elem : base)
				elem /= value;
		}

		template<typename T>
		inline void vector_base<T>::operator+=(const vector_base<T>& oth)
		{
			assert(size() == oth.size());

			for (int i = 0; i < size(); i++)
				base[i] += oth[i];
		}

		template<typename T>
		inline void vector_base<T>::operator-=(const vector_base<T>& oth)
		{
			assert(size() == oth.size());

			for (int i = 0; i < size(); i++)
				base[i] -= oth[i];
		}
	}
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const nm::tybase::vector_base<T>& vct)
{
	auto& vect = vct.stdvect();
	for (auto& elem : vect)
		out << elem << "\n";
	out << typeid(vct).name() << "\n";
	return out;
}

template<typename T, typename V>
inline auto operator+(const V& val, const nm::tybase::vector_base<T>& vct)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, T, V>;

	nm::tybase::vector_base<RT> result(vct.size());
	for (int i = 0; i < vct.size(); i++)
		result[i] = val + vct[i];
	return result;
}

template<typename T, typename V>
inline auto operator-(const V& val, const nm::tybase::vector_base<T>& vct)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, T, V>;

	nm::tybase::vector_base<RT> result(vct.size());
	for (int i = 0; i < vct.size(); i++)
		result[i] = val - vct[i];
	return result;
}

template<typename T, typename V>
inline auto operator*(const V& val, const nm::tybase::vector_base<T>& vct)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, T, V>;

	nm::tybase::vector_base<RT> result(vct.size());
	for (int i = 0; i < vct.size(); i++)
		result[i] = val * vct[i];
	return result;
}

template<typename T, typename V>
inline auto operator/(const V& val, const nm::tybase::vector_base<T>& vct)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, T, V>;

	nm::tybase::vector_base<RT> result(vct.size());
	for (int i = 0; i < vct.size(); i++)
		result[i] = val / vct[i];
	return result;
}

template<typename T, typename V>
inline auto operator+(const nm::tybase::complex_base<V>& cmp, const nm::tybase::vector_base<T>& vct)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, nm::tybase::complex_base<T>, nm::tybase::complex_base<V>>;

	nm::tybase::vector_base<RT> result(vct.size());
	for (int i = 0; i < vct.size(); i++)
		result[i] = cmp + vct[i];
	return result;
}

template<typename T, typename V>
inline auto operator-(const nm::tybase::complex_base<V>& cmp, const nm::tybase::vector_base<T>& vct)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, nm::tybase::complex_base<T>, nm::tybase::complex_base<V>>;

	nm::tybase::vector_base<RT> result(vct.size());
	for (int i = 0; i < vct.size(); i++)
		result[i] = cmp - vct[i];
	return result;
}

template<typename T, typename V>
inline auto operator*(const nm::tybase::complex_base<V>& cmp, const nm::tybase::vector_base<T>& vct)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, nm::tybase::complex_base<T>, nm::tybase::complex_base<V>>;

	nm::tybase::vector_base<RT> result(vct.size());
	for (int i = 0; i < vct.size(); i++)
		result[i] = cmp * vct[i];
	return result;
}

template<typename T, typename V>
inline auto operator/(const nm::tybase::complex_base<V>& cmp, const nm::tybase::vector_base<T>& vct)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, nm::tybase::complex_base<T>, nm::tybase::complex_base<V>>;

	nm::tybase::vector_base<RT> result(vct.size());
	for (int i = 0; i < vct.size(); i++)
		result[i] = cmp / vct[i];
	return result;
}
