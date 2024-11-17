#include "../include/matrix.hpp"
#include "../include/operations.hpp"

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
			auto beg = index < 0 ? 1 : 0;
			for (int i = beg; i < n + beg; i++)
				base[i][i + index] = value;
			return *this;
		}

		template<typename T>
		inline matrix_base<T>& matrix_base<T>::fill_diagonal(vector_base<T> values, int32_t index)
		{
			auto m = rows();
			auto n = m - std::abs(index);
			assert(values.size() == n);

			auto beg = index < 0 ? 1 : 0;
			for (int i = beg; i < n + beg; i++)
				base[i][i + index] = values[i - beg];
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
			return std::make_pair(rows(), cols());
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
		inline vector_base<T> matrix_base<T>::diagonal(int i) const
		{
			auto n = rows() - std::abs(i);
			vector_base<T> diag(n);
			
			auto beg = i < 0 ? 1 : 0;
			for (int k = beg; k < n + beg; k++)
				diag[k - beg] = base[k][k + i];
			return diag;
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
		inline uint128_t matrix_base<T>::row_max() const
		{
			auto m = rows();
			uint128_t imax = 0;
			auto vmax = base[imax].max();
			for (int i = 1; i < m; i++)
			{
				auto cmax = base[i].max();
				if (vmax < cmax)
				{
					imax = i;
					vmax = cmax;
				}
			}
			return imax;
		}

		template<typename T>
		inline uint128_t matrix_base<T>::row_min() const
		{
			auto m = rows();
			uint128_t imin = 0;
			auto vmin = base[imin].min();
			for (int i = 1; i < m; i++)
			{
				auto cmin = base[i].min();
				if (vmin > cmin)
				{
					imin = i;
					vmin = cmin;
				}
			}
			return imin;
		}

		template<typename T>
		inline uint128_t matrix_base<T>::col_max() const
		{
			auto m = rows();
			uint128_t jmax = 0;
			auto vmax = base[0][0];
			for (int i = 0; i < m; i++)
			{
				auto cmax = base[i].imax();
				if (cmax != jmax && base[i][cmax] > vmax)
				{
					jmax = cmax;
					vmax = base[i][cmax];
				}
			}
			return jmax;
		}

		template<typename T>
		inline uint128_t matrix_base<T>::col_min() const
		{
			auto m = rows();
			uint128_t jmin = 0;
			auto vmin = base[0][0];
			for (int i = 0; i < m; i++)
			{
				auto cmin = base[i].imin();
				if (cmin != jmin && base[i][cmin] < vmin)
				{
					jmin = cmin;
					vmin = base[i][cmin];
				}
			}
			return jmin;
		}

		template<typename T>
		inline bool matrix_base<T>::is_square() const
		{
			return rows() == cols();
		}

		template<typename T>
		inline bool matrix_base<T>::is_diagonal() const
		{
			if (!is_square()) return false;

			auto m = rows();
			for (int i = 0; i < m; i++)
				for (int j = 0; j < m; j++)
				{
					if (i == j) continue;
					if (base[i][j] != 0) 
						return false;
				}
		}

		template<typename T>
		inline bool matrix_base<T>::is_triangle() const
		{
			return is_triangleU() || is_triangleL();
		}

		template<typename T>
		inline bool matrix_base<T>::is_triangleU() const
		{
			if (!is_square()) return false;

			auto m = rows();
			for (int i = 0; i < m; i++)
				for (int j = 0; j < i; j++)
					if (base[i][j] != 0)
						return false;

			return true;
		}

		template<typename T>
		inline bool matrix_base<T>::is_triangleL() const
		{
			if (!is_square()) return false;

			auto m = rows();
			for (int i = 0; i < m; i++)
				for (int j = i + 1; j < m; j++)
					if (base[i][j] != 0)
						return false;

			return true;
		}

		template<typename T>
		inline matrix_base<T>& matrix_base<T>::transpose()
		{
			base = transposed().base;
			return *this;
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::transposed() const
		{
			auto [m, n] = size();
			matrix_base result(n, m);
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					result[i][j] = base[j][i];
			return result;
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::inversed() const
		{
			return adjugate() / det();
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::adjugate() const
		{
			assert(is_square());
			auto m = rows();

			matrix_base<T> matr(m);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < m; j++)
					matr[j][i] = pow(-1, i + j + 2) * minor(i, j);
			return matr;
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::conjugate() const
		{
			static_assert(
				typing::is_complex<T>::value,
				"matrix must be complex!"
			);
			auto [m, n] = size();
			matrix_base result(n, m);
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					result[i][j] = base[j][i].conjugate();
			return result;
		}

		template<typename T>
		inline T matrix_base<T>::det() const
		{
			assert(is_square());
			switch (rows())
			{
			case 0:	return 0;
			case 1:	return base[0][0];
			case 2: return base[1][1] * base[0][0] - base[1][0] * base[0][1];
			case 3: return 
				  base[2][2] * base[1][1] * base[0][0]
				- base[0][0] * base[1][2] * base[2][1] 
				- base[0][1] * base[1][0] * base[2][2]
				+ base[0][1] * base[1][2] * base[2][0] 
				+ base[0][2] * base[1][0] * base[2][1]
				- base[0][2] * base[1][1] * base[2][0];

			default:
				return linalg::gauss_determinant(*this);
				break;
			}
		}

		template<typename T>
		inline T matrix_base<T>::minor(uint128_t i) const
		{
			return minor(i, i);
		}

		template<typename T>
		inline T matrix_base<T>::minor(uint128_t in, uint128_t jn) const
		{
			auto [m, n] = size();
			auto ioff = false;
			auto joff = false;

			matrix_base<T> matr(m - 1, n - 1);
			for (int i = 0; i < m; i++)
			{
				if (i == in) { ioff = true; continue; };

				joff = false;
				for (int j = 0; j < n; j++)
				{
					if (j == jn) { joff = true; continue; };
					matr[i - ioff][j - joff] = base[i][j];
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
		inline auto vector_base<T>::dot(const matrix_base<V>& mat) const
		{
			return (*this) * mat;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::dot(const matrix_base<V>& oth) const
		{
			return (*this) * oth;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::dot(const vector_base<V>& vec) const
		{
			return (*this * vec);
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
			auto [l, m] = size();
			auto n = oth.cols();
			assert(m == oth.rows());

			using TS = typing::conditional_t<typing::is_stronger<T, V>::value, T, V>;
			matrix_base<TS> result(l, n);
			for (int i = 0; i < l; i++)
				for (int j = 0; j < n; j++)
				{
					TS sum = 0;
					for (int k = 0; k < m; k++)
						sum += base[i][k] * oth[k][j];
					result[i][j] = sum;
				}

			return result;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator*(const vector_base<V>& vec) const
		{
			auto [m, n] = size();
			assert(n == vec.size());

			using TS = typing::conditional_t<typing::is_stronger<T, V>::value, T, V>;
			vector_base<TS> result(m);
			for (int i = 0; i < m; i++)
			{
				TS sum = 0;
				for (int j = 0; j < n; j++)
					sum += base[i][j] * vec[j];
				result[i] = sum;
			}
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

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const nm::base_type::matrix_base<T>& matrix)
{
	auto [m, n] = matrix.size();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			out << "\t" << matrix[i][j];
		out << "\n";
	}
	out << typeid(matrix).name() << "\n";
	return out;
}