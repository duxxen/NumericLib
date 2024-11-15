#include "../include/vector.hpp"

namespace nm
{
	namespace base_type
	{
		template <typename T>
		vector_base<T>::vector_base(size_t n) :
			base(n)
		{
		}

		template <typename T>
		vector_base<T>::vector_base(size_t n, T value) :
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
		inline vector_base<T>& vector_base<T>::fill(T value)
		{
			for (auto& element : base)
				element = value;
			return *this;
		}

		template<typename T>
		inline uint128_t vector_base<T>::size() const
		{
			return base.size();
		}

		template<typename T>
		inline T& vector_base<T>::operator[](int32_t i)
		{
			if (i < 0)
				return base[base.size() + i];
			return base[i];
		}

		template<typename T>
		inline const T& vector_base<T>::operator[](int32_t i) const
		{
			if (i < 0)
				return base[base.size() + i];
			return base[i];
		}

		template<typename T>
		inline vector_base<T> vector_base<T>::slice(int32_t beg, int32_t end, uint32_t step) const
		{
			int32_t st = step;
			auto n = 1 + std::abs(end - beg) / st;
			if (beg > end)
				st = -st;
			vector_base<T> result(n);
			for (int i = 0; i < n; i++)
				result[i] = (*this)[beg + i * st];
			return result;
		}

		template<typename T>
		inline vector_base<T>& vector_base<T>::sort(bool ascend)
		{
			auto pred = ascend ?
				[](T a, T b) -> bool { return a < b; }
				:
				[](T a, T b) -> bool { return a > b; };

			std::stable_sort(base.begin(), base.end(), pred);
			return *this;
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
			return std::max(base);
		}

		template<typename T>
		inline T vector_base<T>::min() const
		{
			return std::min(base);
		}

		template<typename T>
		inline std::pair<T, T> vector_base<T>::minmax() const
		{
			return std::minmax(base);
		}

		template<typename T>
		inline T vector_base<T>::sum(float32_t p) const
		{
			T sumv = NULL;
			for (auto& element : base)
				sumv += pow(element, p);
			return sumv;
		}

		template<typename T>
		inline float_t vector_base<T>::abs() const
		{
			float_t sumv = NULL;
			for (auto& element : base)
				sumv += pow(nm::abs(element), 2);
			return sqrt(sumv);
		}

		template<typename T>
		inline vector_base<T> vector_base<T>::operator-() const
		{
			auto n = size();
			vector_base<T> result(n);
			for (int i = 0; i < n; i++)
				result[i] = -base[i];
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator+(const vector_base<V>& oth) const
		{
			auto n = size();
			assert(n == oth.size());
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>> result(n);
			for (int i = 0; i < n; i++)
				result[i] = base[i] + oth[i];
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator-(const vector_base<V>& oth) const
		{
			auto n = size();
			assert(n == oth.size());
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>> result(n);
			for (int i = 0; i < n; i++)
				result[i] = base[i] - oth[i];
			return result;
		}

		template<typename T>
		inline vector_base<T>& vector_base<T>::operator+=(const vector_base<T>& oth)
		{
			auto n = size();
			assert(n == oth.size());
			for (int i = 0; i < n; i++)
				base[i] += oth[i];
			return *this;
		}

		template<typename T>
		inline vector_base<T>& vector_base<T>::operator-=(const vector_base<T>& oth)
		{
			auto n = size();
			assert(n == oth.size());
			for (int i = 0; i < n; i++)
				base[i] -= oth[i];
			return *this;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator+(const V& value) const
		{
			auto n = size();
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>> result(n);
			for (int i = 0; i < n; i++)
				result[i] = base[i] + value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator-(const V& value) const
		{
			auto n = size();
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>> result(n);
			for (int i = 0; i < n; i++)
				result[i] = base[i] - value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator*(const V& value) const
		{
			auto n = size();
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>> result(n);
			for (int i = 0; i < n; i++)
				result[i] = value * base[i];
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator/(const V& value) const
		{
			auto n = size();
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>> result(n);
			for (int i = 0; i < n; i++)
				result[i] = base[i] / value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator+(const complex_base<V>& value) const
		{
			auto n = size();
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<complex_base<T>>, vector_base<complex_base<V>>> result(n);
			for (int i = 0; i < n; i++)
				result[i] = base[i] + value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator-(const complex_base<V>& value) const
		{
			auto n = size();
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<complex_base<T>>, vector_base<complex_base<V>>> result(n);
			for (int i = 0; i < n; i++)
				result[i] = base[i] - value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator*(const complex_base<V>& value) const
		{
			auto n = size();
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<complex_base<T>>, vector_base<complex_base<V>>> result(n);
			for (int i = 0; i < n; i++)
				result[i] = base[i] * value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator/(const complex_base<V>& value) const
		{
			auto n = size();
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<complex_base<T>>, vector_base<complex_base<V>>> result(n);
			for (int i = 0; i < n; i++)
				result[i] = base[i] / value;
			return result;
		}

		template<typename T>
		inline vector_base<T>& vector_base<T>::operator+=(const T& value)
		{
			for (int i = 0; i < size(); i++)
				base[i] += value;
			return *this;
		}

		template<typename T>
		inline vector_base<T>& vector_base<T>::operator-=(const T& value)
		{
			for (int i = 0; i < size(); i++)
				base[i] -= value;
			return *this;
		}

		template<typename T>
		inline vector_base<T>& vector_base<T>::operator*=(const T& value)
		{
			for (int i = 0; i < size(); i++)
				base[i] *= value;
			return *this;
		}

		template<typename T>
		inline vector_base<T>& vector_base<T>::operator/=(const T& value)
		{
			for (int i = 0; i < size(); i++)
				base[i] /= value;
			return *this;
		}
	}
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const nm::base_type::vector_base<T>& vector)
{
	for (auto& elem : vector.base)
		out << elem << "\n";
	out << typeid(vector).name() << "\n";
	return out;
}

template<typename T, typename V>
inline auto operator+(const V& value, const nm::base_type::vector_base<T>& vector)
{
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, nm::base_type::vector_base<T>, nm::base_type::vector_base<V>> result(vector.size());
	for (int i = 0; i < vector.size(); i++)
		result[i] = value + vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator-(const V& value, const nm::base_type::vector_base<T>& vector)
{
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, nm::base_type::vector_base<T>, nm::base_type::vector_base<V>> result(vector.size());
	for (int i = 0; i < vector.size(); i++)
		result[i] = value - vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator*(const V& value, const nm::base_type::vector_base<T>& vector)
{
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, nm::base_type::vector_base<T>, nm::base_type::vector_base<V>> result(vector.size());
	for (int i = 0; i < vector.size(); i++)
		result[i] = value * vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator/(const V& value, const nm::base_type::vector_base<T>& vector)
{
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, nm::base_type::vector_base<T>, nm::base_type::vector_base<V>> result(vector.size());
	for (int i = 0; i < vector.size(); i++)
		result[i] = value / vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator+(const nm::base_type::complex_base<V>& value, const nm::base_type::vector_base<T>& vector)
{
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, nm::base_type::vector_base<nm::base_type::complex_base<T>>, nm::base_type::vector_base<nm::base_type::complex_base<V>>> result(vector.size());
	for (int i = 0; i < vector.size(); i++)
		result[i] = value + vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator-(const nm::base_type::complex_base<V>& value, const nm::base_type::vector_base<T>& vector)
{
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, nm::base_type::vector_base<nm::base_type::complex_base<T>>, nm::base_type::vector_base<nm::base_type::complex_base<V>>> result(vector.size());
	for (int i = 0; i < vector.size(); i++)
		result[i] = value - vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator*(const nm::base_type::complex_base<V>& value, const nm::base_type::vector_base<T>& vector)
{
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, nm::base_type::vector_base<nm::base_type::complex_base<T>>, nm::base_type::vector_base<nm::base_type::complex_base<V>>> result(vector.size());
	for (int i = 0; i < vector.size(); i++)
		result[i] = value * vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator/(const nm::base_type::complex_base<V>& value, const nm::base_type::vector_base<T>& vector)
{
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, nm::base_type::vector_base<nm::base_type::complex_base<T>>, nm::base_type::vector_base<nm::base_type::complex_base<V>>> result(vector.size());
	for (int i = 0; i < vector.size(); i++)
		result[i] = value / vector.base[i];
	return result;
}

