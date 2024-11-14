#include "../include/matrix.hpp"

namespace nm
{
	namespace base_type
	{
		template<typename T>
		inline matrix_base<T>::matrix_base(uint128_t mn) :
			base(mn, vector_base<T>(mn))
		{
		}

		template<typename T>
		inline matrix_base<T>::matrix_base(uint128_t m, uint128_t n) :
			base(m, vector_base<T>(n))
		{
		}

		template<typename T>
		inline matrix_base<T>::matrix_base(uint128_t m, uint128_t n, T value) :
			base(m, vector_base<T>(n, value))
		{
		}

		template<typename T>
		inline matrix_base<T>::matrix_base(const std::vector<std::vector<T>>& stdmatr)
		{
			for (auto& vector : stdmatr)
				base.push_back(vector);
		}

		template<typename T>
		inline matrix_base<T>::matrix_base(const std::initializer_list<std::initializer_list<T>>& rawmatr)
		{
			for (auto& vector : rawmatr)
				base.push_back(vector);
		}

		template<typename T>
		inline uint128_t matrix_base<T>::rows() const
		{
			return base.size();
		}

		template<typename T>
		inline uint128_t matrix_base<T>::cols() const
		{
			if (base.empty())
				return 0;
			return base.front().size();
		}

		template<typename T>
		inline std::pair<uint128_t, uint128_t> matrix_base<T>::size() const
		{
			if (base.empty())
				return std::make_pair(0, 0);
			return std::make_pair(base.size(), base.front().size());
		}

		template<typename T>
		inline vector_base<T>& matrix_base<T>::operator[](int i)
		{
			return base[i];
		}

		template<typename T>
		inline const vector_base<T>& matrix_base<T>::operator[](int i) const
		{
			return base[i];
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::operator-() const
		{
			auto m = rows();
			auto n = cols();
			matrix_base<T> result(m, n);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
					result[i][j] = -base[i][j];
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator+(const matrix_base<V>& oth) const
		{
			auto m = rows();
			auto n = cols();
			assert(std::make_pair(m, n) == oth.size());
			typing::conditional_t<typing::is_stronger<T, V>::value, matrix_base<T>, matrix_base<V>> result(m, n);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
					result[i][j] = base[i][j] + oth[i][j];
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator-(const matrix_base<V>& oth) const
		{
			auto m = rows();
			auto n = cols();
			assert(std::make_pair(m, n) == oth.size());
			typing::conditional_t<typing::is_stronger<T, V>::value, matrix_base<T>, matrix_base<V>> result(m, n);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
					result[i][j] = base[i][j] - oth[i][j];
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator*(const matrix_base<V>& oth) const
		{
		}

		template<typename T>
		inline matrix_base<T>& matrix_base<T>::operator+=(const matrix_base<T>& oth)
		{
			auto m = rows();
			auto n = cols();
			assert(std::make_pair(m, n) == oth.size());
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
					base[i][j] += oth[i][j];
			return *this;
		}

		template<typename T>
		inline matrix_base<T>& matrix_base<T>::operator-=(const matrix_base<T>& oth)
		{
			auto m = rows();
			auto n = cols();
			assert(std::make_pair(m, n) == oth.size());
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
					base[i][j] -= oth[i][j];
			return *this;
		}

		template<typename T>
		inline matrix_base<T>& matrix_base<T>::operator*=(const matrix_base<T>& oth)
		{
			return *this;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator+(const V& value) const
		{
			auto m = rows();
			auto n = cols();
			typing::conditional_t<typing::is_stronger<T, V>::value, matrix_base<T>, matrix_base<V>> result(m, n);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
					result[i][j] = base[i][j] + value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator-(const V& value) const
		{
			auto m = rows();
			auto n = cols();
			typing::conditional_t<typing::is_stronger<T, V>::value, matrix_base<T>, matrix_base<V>> result(m, n);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
					result[i][j] = base[i][j] - value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator*(const V& value) const
		{
			auto m = rows();
			auto n = cols();
			typing::conditional_t<typing::is_stronger<T, V>::value, matrix_base<T>, matrix_base<V>> result(m, n);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
					result[i][j] = base[i][j] * value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator/(const V& value) const
		{
			auto m = rows();
			auto n = cols();
			typing::conditional_t<typing::is_stronger<T, V>::value, matrix_base<T>, matrix_base<V>> result(m, n);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
					result[i][j] = base[i][j] / value;
			return result;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator+(const complex_base<V>& value) const
		{

		}
	}
}