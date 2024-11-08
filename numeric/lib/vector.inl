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
		inline uint128_t vector_base<T>::size() const
		{
			return base.size();
		}

		template<typename T>
		inline float_t vector_base<T>::abs() const
		{
			float_t sumq = 0;
			for (int i = 0; i < size(); i++)
				sumq += pow(abs(base[i]), 2);
			return sqrt(sumq);
		}

		template<typename T>
		inline vector_base<T>& vector_base<T>::normalize()
		{
			auto len = abs();
			for (int i = 0; i < size(); i++)
				base[i] /= len;
			return *this;
		}

		template<typename T>
		inline vector_base<T> vector_base<T>::normalized() const
		{
			auto result(*this);
			auto len = abs();
			for (int i = 0; i < size(); i++)
				result[i] /= len;
			return result;
		}

		template<typename T>
		inline T& vector_base<T>::operator[](int i)
		{
			return base[i];
		}

		template<typename T>
		inline const T& vector_base<T>::operator[](int i) const
		{
			return base[i];
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator+(const vector_base<V>& oth) const
		{
			assert(size() == oth.size());
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] + oth[i];
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator-(const vector_base<V>& oth) const
		{
			assert(size() == oth.size());
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] - oth[i];
			return result;
		}

		template<typename T>
		inline vector_base<T>& vector_base<T>::operator+=(const vector_base<T>& oth)
		{
			assert(size() == oth.size());
			for (int i = 0; i < size(); i++)
				base[i] += oth[i];
			return *this;
		}

		template<typename T>
		inline vector_base<T>& vector_base<T>::operator-=(const vector_base<T>& oth)
		{
			assert(size() == oth.size());
			for (int i = 0; i < size(); i++)
				base[i] -= oth[i];
			return *this;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator+(const V& value) const
		{
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] + value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator-(const V& value) const
		{
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] - value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator*(const V& value) const
		{
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = value * base[i];
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator/(const V& value) const
		{
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] / value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator+(const complex_base<V>& value) const
		{
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<complex_base<T>>, vector_base<complex_base<V>>> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] + value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator-(const complex_base<V>& value) const
		{
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<complex_base<T>>, vector_base<complex_base<V>>> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] - value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator*(const complex_base<V>& value) const
		{
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<complex_base<T>>, vector_base<complex_base<V>>> result(size());
			for (int i = 0; i < size(); i++)
				result[i] = base[i] * value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::operator/(const complex_base<V>& value) const
		{
			typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<complex_base<T>>, vector_base<complex_base<V>>> result(size());
			for (int i = 0; i < size(); i++)
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

