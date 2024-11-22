#include "../include/vector.hpp"

namespace nm
{
	namespace base_type
	{
		template <typename T>
		vector_base<T>::vector_base(uint128_t n) :
			base(n)
		{
		}

		template <typename T>
		vector_base<T>::vector_base(uint128_t n, T value) :
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
			return *std::max_element(base.begin(), base.end());
		}

		template<typename T>
		inline T vector_base<T>::min() const
		{
			return *std::min_element(base.begin(), base.end());
		}

		template<typename T>
		inline std::pair<T, T> vector_base<T>::minmax() const
		{
			return *std::minmax_element(base.begin(), base.end());
		}

		template<typename T>
		inline uint128_t vector_base<T>::imax() const
		{
			return std::distance(base.begin(), std::max_element(base.begin(), base.end()));
		}

		template<typename T>
		inline uint128_t vector_base<T>::imin() const
		{
			return std::distance(base.begin(), std::min_element(base.begin(), base.end()));
		}

		template<typename T>
		inline std::pair<T, T> vector_base<T>::iminmax() const
		{
			auto [imn, imx] = std::minmax_element(base.begin(), base.end());
			return std::make_pair(
				std::distance(base.begin(), imn),
				std::distance(base.begin(), imx)
			);
		}

		template<typename T>
		inline T vector_base<T>::sum() const
		{
			T sumv = NULL;
			for (auto& element : base)
				sumv += element;
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
		inline T vector_base<T>::norm1() const
		{
			T sumv = 0;
			for (auto& element : base)
				sumv += nm::abs(element);
			return sumv;
		}

		template<typename T>
		inline T vector_base<T>::norm2() const
		{
			return abs();
		}

		template<typename T>
		inline T vector_base<T>::normi() const
		{
			T amax = nm::abs(base[0]);
			for (auto& element : base)
				amax = nm::abs(element);
			return amax;
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
		inline auto vector_base<T>::dot(const vector_base<V>& oth) const
		{
			using TS = typing::conditional_t(typing::is_stronger<T, V>(), T, V);
			TS product = 0;
			auto n = size();
			assert(n == oth.size());
			for (int i = 0; i < n; i++)
				product += base[i] * oth[i];
			return product;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::cross(const vector_base<V>& oth) const
		{
			assert(size() == oth.size() && size() == 3);
			using TS = typing::conditional_t(typing::is_stronger<T, V>(), T, V);

			return vector_base<TS>({
				base[1] * oth[2] - base[2] * oth[1],
				base[2] * oth[0] - base[0] * oth[2],
				base[0] * oth[1] - base[1] * oth[0]
			});
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
	using VT = nm::base_type::vector_base<T>;
	using VV  = nm::base_type::vector_base<V>;
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, VT, VV> result(vector.size());
	for (int i = 0; i < vector.size(); i++)
		result[i] = value + vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator-(const V& value, const nm::base_type::vector_base<T>& vector)
{
	using VT = nm::base_type::vector_base<T>;
	using VV = nm::base_type::vector_base<V>;
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, VT, VV> result(vector.size());
	for (int i = 0; i < vector.size(); i++)
		result[i] = value - vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator*(const V& value, const nm::base_type::vector_base<T>& vector)
{
	using VT = nm::base_type::vector_base<T>;
	using VV = nm::base_type::vector_base<V>;
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, VT, VV> result(vector.size());
	for (int i = 0; i < vector.size(); i++)
		result[i] = value * vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator/(const V& value, const nm::base_type::vector_base<T>& vector)
{
	using VT = nm::base_type::vector_base<T>;
	using VV = nm::base_type::vector_base<V>;
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, VT, VV> result(vector.size());
	for (int i = 0; i < vector.size(); i++)
		result[i] = value / vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator+(const nm::base_type::complex_base<V>& value, const nm::base_type::vector_base<T>& vector)
{
	using CT = nm::base_type::complex_base<T>;
	using CV = nm::base_type::complex_base<V>;
	using VT = nm::base_type::vector_base<CT>;
	using VV = nm::base_type::vector_base<CV>;
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, VT, VV> result(vector.size());

	for (int i = 0; i < vector.size(); i++)
		result[i] = value + vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator-(const nm::base_type::complex_base<V>& value, const nm::base_type::vector_base<T>& vector)
{
	using CT = nm::base_type::complex_base<T>;
	using CV = nm::base_type::complex_base<V>;
	using VT = nm::base_type::vector_base<CT>;
	using VV = nm::base_type::vector_base<CV>;
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, VT, VV> result(vector.size());

	for (int i = 0; i < vector.size(); i++)
		result[i] = value - vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator*(const nm::base_type::complex_base<V>& value, const nm::base_type::vector_base<T>& vector)
{
	using CT = nm::base_type::complex_base<T>;
	using CV = nm::base_type::complex_base<V>;
	using VT = nm::base_type::vector_base<CT>;
	using VV = nm::base_type::vector_base<CV>;
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, VT, VV> result(vector.size());

	for (int i = 0; i < vector.size(); i++)
		result[i] = value * vector.base[i];
	return result;
}

template<typename T, typename V>
inline auto operator/(const nm::base_type::complex_base<V>& value, const nm::base_type::vector_base<T>& vector)
{
	using CT = nm::base_type::complex_base<T>;
	using CV = nm::base_type::complex_base<V>;
	using VT = nm::base_type::vector_base<CT>;
	using VV = nm::base_type::vector_base<CV>;
	nm::typing::conditional_t<nm::typing::is_stronger<T, V>::value, VT, VV> result(vector.size());

	for (int i = 0; i < vector.size(); i++)
		result[i] = value / vector.base[i];
	return result;
}

