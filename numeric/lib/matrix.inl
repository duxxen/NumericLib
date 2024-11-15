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
		inline matrix_base<T>& matrix_base<T>::fill(T value)
		{
			for (auto& vect : base)
				vect.fill(value);
			return *this;
		}

		template<typename T>
		inline matrix_base<T>& matrix_base<T>::fill_diagonal(T value, int32_t index)
		{
			auto n = rows() - std::abs(index);
			for (int i = 0; i < n; i++)
				base[i][i + index] = value;
			return *this;
		}

		template<typename T>
		inline matrix_base<T>& matrix_base<T>::fill_diagonal(vector_base<T> values, int32_t index)
		{
			auto m = rows();
			auto n = m - std::abs(index);
			assert(values.size() == n);
			for (int i = 0; i < n; i++)
				base[i][i + index] = values[i];
			return *this;
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
		inline vector_base<T>& matrix_base<T>::row(int i)
		{
			if (i < 0)
				return base[base.size() + i];
			return base[i];
		}

		template<typename T>
		inline const vector_base<T>& matrix_base<T>::row(int i) const
		{
			if (i < 0)
				return base[base.size() + i];
			return base[i];
		}

		template<typename T>
		inline vector_base<T> matrix_base<T>::col(int i) const
		{
			auto [m, n] = size();
			if (i < 0)
				i = n + i;

			vector_base<T> result(n);
			for (int j = 0; j < m; j++)
				result[j] = base[j][i];
			return result;
		}

		template<typename T>
		inline vector_base<T>& matrix_base<T>::operator[](int i)
		{
			return row(i);
		}

		template<typename T>
		inline const vector_base<T>& matrix_base<T>::operator[](int i) const
		{
			return row(i);
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::slice(int32_t rbeg, int32_t rend, int32_t cbeg, int32_t cend, uint32_t rstep, uint32_t cstep)
		{
			int32_t rst = rstep;
			auto m = 1 + std::abs(rend - rbeg) / rstep;
			auto n = 1 + std::abs(cend - cbeg) / cstep;
			if (rbeg > rend) rst = -rst;

			matrix_base<T> result(m, n);
			for (int i = 0; i < m; i++)
				result[i] = (*this)[rbeg + i * rst].slice(cbeg, cend, cstep);
			return result;
		}

		template<typename T>
		inline bool matrix_base<T>::is_square() const
		{
			return rows() == cols();
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::inversed() const
		{
			return matrix_base();
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::adjugate() const
		{
			return matrix_base();
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::conjugate() const
		{
			return matrix_base();
		}

		template<typename T>
		inline float_t matrix_base<T>::det() const
		{
			assert(is_square());
			switch (rows())
			{
			case 0:	return 0;
			case 1:	return base[0][0];
			case 2: return base[1][1] * base[0][0] - base[1][0] * base[0][1];
			case 3: return 
				+ base[2][2] * base[1][1] * base[0][0]
				- base[0][0] * base[1][2] * base[2][1] 
				- base[0][1] * base[1][0] * base[2][2]
				+ base[0][1] * base[1][2] * base[2][0] 
				+ base[0][2] * base[1][0] * base[2][1]
				- base[0][2] * base[1][1] * base[2][0];

			default:
				break;
			}
		}

		template<typename T>
		inline float_t matrix_base<T>::minor(uint128_t i) const
		{
			return minor(i, i);
		}

		template<typename T>
		inline float_t matrix_base<T>::minor(uint128_t in, uint128_t jn) const
		{
			auto [m, n] = size();
			auto ioff = false;
			auto joff = false;

			matrix_base<T> matr(m - 1, n - 1);
			for (int i = 0; i < m - 1; i++)
			{
				if (i == in) { ioff = true; continue; };
				for (int j = 0; j < n - 1; j++)
				{
					if (j == jn) { joff = true; continue; };
					matr[i][j] = base[i + ioff][j + joff];
				}
			}

			return matr.det();
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::operator-() const
		{
			auto [m, n] = size();
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
			auto [m, n] = size();
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
			auto [m, n] = size();
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
		template<typename V>
		inline auto matrix_base<T>::operator*(const vector_base<V>& vec) const
		{
			auto [m, n] = size();
			using TV = typing::conditional_t<typing::is_stronger<T, V>::value, vector_base<T>, vector_base<V>>;
			TV result(m);
			return result;
		}

		template<typename T>
		inline matrix_base<T>& matrix_base<T>::operator+=(const matrix_base<T>& oth)
		{
			auto [m, n] = size();
			assert(std::make_pair(m, n) == oth.size());
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
					base[i][j] += oth[i][j];
			return *this;
		}

		template<typename T>
		inline matrix_base<T>& matrix_base<T>::operator-=(const matrix_base<T>& oth)
		{
			auto [m, n] = size();
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
			auto [m, n] = size();
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
			auto [m, n] = size();
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
			auto [m, n] = size();
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
			auto [m, n] = size();
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