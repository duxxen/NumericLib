#include "matrix.hpp"
#include "../linalg/operations.hpp"

namespace nm
{
	namespace tybase
	{
		template<typename T>
		inline matrix_base<T>::matrix_base(size2D_t mn) :
			vector_base<T>(mn.first * mn.second),
			rows_(mn.first),
			cols_(mn.second)
		{
		}

		template<typename T>
		inline matrix_base<T>::matrix_base(size2D_t mn, T value) :
			vector_base<T>(mn.first * mn.second, value),
			rows_(mn.first),
			cols_(mn.second)
		{
		}

		template<typename T>
		inline matrix_base<T>::matrix_base(size1D_t m, size1D_t n) :
			vector_base<T>(m * n),
			rows_(m),
			cols_(n)
		{
		}

		template<typename T>
		inline matrix_base<T>::matrix_base(size1D_t m, size1D_t n, T value) :
			vector_base<T>(m * n, value),
			rows_(m),
			cols_(n)
		{
		}

		template<typename T>
		inline matrix_base<T>::matrix_base(size2D_t mn, const vector_base<T>& vect) :
			vector_base<T>(vect),
			rows_(mn.first),
			cols_(mn.second)
		{
		}

		template<typename T>
		inline matrix_base<T>::matrix_base(size1D_t m, size1D_t n, const vector_base<T>& vect) :
			vector_base<T>(vect),
			rows_(m),
			cols_(n)
		{
		}

		template<typename T>
		inline matrix_base<T>::matrix_base(const std::initializer_list<std::initializer_list<T>>& rawmatr) :
			vector_base<T>(rawmatr.size() *rawmatr.begin()->size()),
			rows_(rawmatr.size()),
			cols_(rawmatr.begin()->size())
		{
			for (int i = 0; i < rows_; i++)
			{
				auto row = rawmatr.begin() + i;
				for (int j = 0; j < cols_; j++)
					this->base[cols_ * i + j] = *(row->begin() + j);
			}
		}

		template<typename T>
		inline void matrix_base<T>::fill_diagonal(T value, int32_t index)
		{
			auto iof = index >= 0 ? index : 0;
			auto jof = index < 0 ? -index : 0;
			for (int i = 0; i < rows_; i++)
			{
				if (i + iof >= rows_ || i + jof >= cols_)
					break;
				(*this)(i + iof, i + jof) = value;
			}
		}

		template<typename T>
		inline void matrix_base<T>::fill_diagonal(const vector_base<T>& values, int32_t index)
		{
			auto iof = 0;
			auto jof = 0;
			if (index >= 0) {
				iof = index;
				assert(values.size() == rows_ - iof);
			}
			else {
				jof = -index;
				assert(values.size() == cols_ - jof);
			}

			for (int i = 0; i < values.size(); i++)
				(*this)(i + iof, i + jof) = values[i];
		}

		template<typename T>
		inline void matrix_base<T>::append_row(const vector_base<T>& vct)
		{
			if (rows_ == 0)
			{
				this->base = vct.stdvect();
				rows_ = 1;
				cols_ = vct.size();
				return;
			}

			assert(vct.size() == cols_);
			vector_base<T>::append(vct);
			rows_++;
		}

		template<typename T>
		inline void matrix_base<T>::append_col(const vector_base<T>& vct)
		{
			if (cols_ == 0)
			{
				this->base = vct.stdvect();
				rows_ = vct.size();
				cols_ = 1;
				return;
			}

			assert(vct.size() == rows_);
			auto offs = 0;
			for (int i = 0; i < rows_; i++)
			{
				vector_base<T>::insert(cols_ * i + (cols_ - offs), vct[i]);
				if (i == 0) {
					cols_++;
					offs++;
				};
			}
		}

		template<typename T>
		inline void matrix_base<T>::append(const vector_base<T>& vct, bool isrow)
		{
			isrow ? append_row(vct) : append_col(vct);
		}

		template<typename T>
		inline void matrix_base<T>::insert_row(int32_t ind, const vector_base<T>& vct)
		{
			assert(vct.size() == cols_);
			vector_base<T>::insert(cols_ * ind, vct);
			rows_++;
		}

		template<typename T>
		inline void matrix_base<T>::insert_col(int32_t ind, const vector_base<T>& vct)
		{
			assert(vct.size() == rows_);
			if (ind < 0) ind = rows_ + ind;
			for (int i = 0; i < rows_; i++)
			{
				vector_base<T>::insert(cols_ * i + ind, vct[i]);
				if (i == 0) cols_++;
			}
		}

		template<typename T>
		inline void matrix_base<T>::insert(int32_t ind, const vector_base<T>& vct, bool isrow)
		{
			isrow ? insert_row(ind, vct) : insert_col(ind, vct);
		}

		template<typename T>
		inline size1D_t matrix_base<T>::rows() const
		{
			return rows_;
		}

		template<typename T>
		inline size1D_t matrix_base<T>::cols() const
		{
			return cols_;
		}

		template<typename T>
		inline size2D_t matrix_base<T>::size() const
		{
			return size2D_t(rows_, cols_);
		}

		template<typename T>
		inline T& matrix_base<T>::operator()(int128_t i, int128_t j)
		{
			if (i < 0) i += rows_;
			if (j < 0) j += cols_;
			return (*this)[cols_ * i + j];
		}

		template<typename T>
		inline const T& matrix_base<T>::operator()(int128_t i, int128_t j) const
		{
			if (i < 0) i += rows_;
			if (j < 0) j += cols_;
			return (*this)[cols_ * i + j];
		}

		template<typename T>
		inline vector_base<T> matrix_base<T>::row(int128_t i)
		{
			auto beg = cols_ * i;
			auto end = beg + cols_ - 1;
			return vector_base<T>::slice(beg, end);
		}

		template<typename T>
		inline vector_base<T> matrix_base<T>::col(int128_t i) const
		{
			auto beg = i;
			auto end = beg + rows_ + cols_;
			auto stp = cols_;
			return vector_base<T>::slice(beg, end, stp);
		}

		template<typename T>
		inline vector_base<T> matrix_base<T>::diagonal(int128_t index) const
		{
			auto iof = index >= 0 ? index : 0;
			auto jof = index < 0 ? -index : 0;
			int128_t szd = rows_ - cols_;

			auto stp = cols_ + 1; 
			auto beg = cols_ * iof + jof;
			auto endi = beg + (rows_ - iof - 1) * stp;
			auto endj = beg + (cols_ - jof - 1) * stp;
			
			if (szd == 0) {
				if (iof)	return vector_base<T>::slice(beg, endi, stp);
				else		return vector_base<T>::slice(beg, endj, stp);
			}
			else if (szd > 0) {
				if (iof <= cols_)	return vector_base<T>::slice(beg, endj, stp);
				else				return vector_base<T>::slice(beg, endi, stp);
			}
			else {
				if (jof >= rows_)	return vector_base<T>::slice(beg, endj, stp);
				else				return vector_base<T>::slice(beg, endi, stp);
			}
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::slice(int32_t rbeg, int32_t rend, int32_t cbeg, int32_t cend, uint32_t rstp, uint32_t cstp)
		{
			int32_t rst = rstp;
			int32_t cst = cstp;
			auto m = 1 + std::abs(rend - rbeg) / rstp;
			auto n = 1 + std::abs(cend - cbeg) / cstp;
			if (rbeg > rend) rst = -rst;
			if (cbeg > cend) cst = -cst;

			matrix_base<T> result;
			for (int i = 0; i < m; i++)
				result.append_row(vector_base<T>::slice(
					cols_ * (rbeg + i * rst) + cbeg, 
					cols_ * (rbeg + i * rst) + cend, 
					cstp
				));
			return result;
		}

		template<typename T>
		inline size2D_t matrix_base<T>::argmax() const
		{
			auto ind = vector_base<T>::argmax();
			return size2D_t(ind / rows_, ind % cols_);
		}

		template<typename T>
		inline size2D_t matrix_base<T>::argmin() const
		{
			auto ind = vector_base<T>::argmin();
			return size2D_t(ind / rows_, ind % cols_);
		}

		template<typename T>
		inline std::pair<size2D_t, size2D_t> matrix_base<T>::argminmax() const
		{
			auto [imin, imax] = vector_base<T>::argminmax();
			return std::make_pair(
				size2D_t(imin / rows_, imin % cols_),
				size2D_t(imax / rows_, imax % cols_)
			);
		}

		template<typename T>
		inline void matrix_base<T>::transpose()
		{
			auto copy = this->base;
			for (int i = 0; i < rows_; i++)
				for (int j = 0; j < cols_; j++)
					this->base[rows_ * j + i] = copy[cols_ * i + j];
			std::swap(rows_, cols_);
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::transposed() const
		{
			matrix_base<T> mtr(*this);
			mtr.transpose();
			return mtr;
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::inversed() const
		{
			assert(is_square());
			auto m = rows();
			auto d = det();

			matrix_base<T> matr(m, m);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < m; j++)
					matr(j, i) = pow(-1, i + j + 2) * minor(i, j) / d;
			return matr;
		}

		template<typename T>
		inline bool matrix_base<T>::is_square() const
		{
			return rows_ == cols_;
		}

		template<typename T>
		inline bool matrix_base<T>::is_diagonal() const
		{
			if (!is_square()) return false;

			for (int i = 0; i < rows_; i++)
				for (int j = 0; j < cols_; j++)
				{
					if (i == j) continue;
					if ((*this)(i, j) != 0)
						return false;
				}
			return true;
		}

		template<typename T>
		inline bool matrix_base<T>::is_triangle() const
		{
			return is_triangleL() || is_triangleU();
		}

		template<typename T>
		inline bool matrix_base<T>::is_triangleL() const
		{
			if (!is_square()) return false;

			for (int i = 0; i < rows_; i++)
				for (int j = 0; j < i; j++)
					if ((*this)(i, j) != 0)
						return false;
			
			return true;
		}

		template<typename T>
		inline bool matrix_base<T>::is_triangleU() const
		{
			if (!is_square()) return false;

			for (int i = 0; i < rows_; i++)
				for (int j = i+1; j < cols_; j++)
					if ((*this)(i, j) != 0)
						return false;

			return true;
		}

		template<typename T>
		inline auto matrix_base<T>::norm1() const
		{
			using RT = tycomp::inner_switch<tycomp::is_complex<T>::value, T>::inner;

			RT max = 0;
			for (int j = 0; j < cols_; j++)
			{
				RT sum = 0;
				for (int i = 0; i < rows_; i++)
					sum += (*this)(i, j);
				max = nm::max(max, sum);
			}

			return max;
		}

		template<typename T>
		inline auto matrix_base<T>::norm2() const
		{
			using RT = tycomp::inner_switch<tycomp::is_complex<T>::value, T>::inner;
			RT sum = 0;
			for (int i = 0; i < rows_; i++)
				for (int j = 0; j < cols_; j++)
					sum += nm::pow(nm::abs((*this)(i, j)), 2);
			return nm::sqrt(sum);
		}

		template<typename T>
		inline auto matrix_base<T>::normi() const
		{
			using RT = tycomp::inner_switch<tycomp::is_complex<T>::value, T>::inner;

			RT max = 0;
			for (int i = 0; i < rows_; i++)
			{
				RT sum = 0;
				for (int j = 0; j < cols_; j++)
					sum += (*this)(i, j);
				max = nm::max(max, sum);
			}

			return max;
		}

		template<typename T>
		inline auto matrix_base<T>::norme() const
		{
			return vector_base<T>::norme();
		}

		template<typename T>
		inline auto matrix_base<T>::normp(const uint32_t& p) const
		{
			return normpq(p, 1);
		}

		template<typename T>
		inline auto matrix_base<T>::normpq(const uint32_t& p, const uint32_t& q) const
		{
			using RT = tycomp::inner_switch<tycomp::is_complex<T>::value, T>::inner;
			RT sum = 0;
			for (int j = 0; j < cols_; j++)
			{
				for (int i = 0; i < rows_; i++)
					sum += nm::pow(nm::abs((*this)(i, j)), p);
				sum = nm::pow(sum, (float64_t)q / p);
			}
			return nm::pow(sum, 1.0 / p);
		}

		template<typename T>
		inline auto matrix_base<T>::minor(int128_t i) const
		{
			return minor(i, i);
		}

		template<typename T>
		inline auto matrix_base<T>::minor(int128_t in, int128_t jn) const
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
					matr(i - ioff, j - joff) = (*this)(i, j);
				}
			}
			return matr.det();
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::operator-() const
		{
			return matrix_base<T>(size(), vector_base<T>::operator-());
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::dot(const matrix_base<V>& oth) const
		{
			return (*this) * oth;
		}

		template<typename T>
		template<typename V>
		inline auto vector_base<T>::dot(const matrix_base<V>& mat) const
		{
			return (*this) * mat;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::dot(const vector_base<V>& vct) const
		{
			return (*this) * vct;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator+(const V& value) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;
			return matrix_base<RT>(size(), vector_base<T>::operator+(value));
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator-(const V& value) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;
			return matrix_base<RT>(size(), vector_base<T>::operator-(value));
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator*(const V& value) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;
			return matrix_base<RT>(size(), vector_base<T>::operator*(value));
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator/(const V& value) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;
			return matrix_base<RT>(size(), vector_base<T>::operator/(value));
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator+(const complex_base<V>& value) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>;
			return matrix_base<RT>(size(), vector_base<T>::operator-(value));
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator-(const complex_base<V>& value) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>;
			return matrix_base<RT>(size(), vector_base<T>::operator-(value));
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator*(const complex_base<V>& value) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>;
			return matrix_base<RT>(size(), vector_base<T>::operator-(value));
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator/(const complex_base<V>& value) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, complex_base<T>, complex_base<V>>;
			return matrix_base<RT>(size(), vector_base<T>::operator-(value));
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator+(const matrix_base<V>& oth) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;
			return matrix_base<RT>(size(), vector_base<T>::operator+(vector_base<T>(oth)));
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator-(const matrix_base<V>& oth) const
		{
			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;
			return matrix_base<RT>(size(), vector_base<T>::operator-(vector_base<T>(oth)));
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator*(const matrix_base<V>& oth) const
		{
			auto [l, m] = size();
			auto n = oth.cols();
			assert(m == oth.rows());

			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;
			matrix_base<RT> result(l, n);
			for (int i = 0; i < l; i++)
				for (int j = 0; j < n; j++)
				{
					RT sum = 0;
					for (int k = 0; k < m; k++)
						sum += (*this)(i, k) * oth(k, j);
					result(i, j) = sum;
				}

			return result;
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator*(const vector_base<V>& vct) const
		{
			auto [m, n] = size();
			assert(n == vct.size());

			using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;
			vector_base<RT> result(m);
			for (int i = 0; i < m; i++)
			{
				RT sum = 0;
				for (int j = 0; j < n; j++)
					sum += (*this)(i, j) * vct[j];
				result[i] = sum;
			}
			return result;
		}
	}

	matrf_t identity(size1D_t n)
	{
		return diagonal<float_t>(n, 1);
	}

	matrf_t triangle_l(size1D_t n)
	{
		matrf_t tri(n, n, 0);
		for (int i = 0; i < n; i++)
			for (int j = 0; j <= i; j++)
				tri(i, j) = 1;
		return tri;
	}

	matrf_t triangle_u(size1D_t n)
	{
		matrf_t tri(n, n, 0);
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++)
				tri(i, j) = 1;
		return tri;
	}

	matrf_t zeros(size2D_t n)
	{
		return zeros<float_t>(n);
	}

	template <typename T>
	tybase::matrix_base<T> zeros(size2D_t n)
	{
		return tybase::matrix_base<T>(n, 0);
	}

	template<typename T>
	tybase::matrix_base<T> diagonal(size1D_t n, const T& value)
	{
		tybase::matrix_base<T> diag(n, n);
		diag.fill_diagonal(value);
		return diag;
	}

	template<typename T>
	tybase::matrix_base<T> diagonal(const tybase::vector_base<T>& values)
	{
		auto n = values.size();
		tybase::matrix_base<T> diag(n, n);
		diag.fill_diagonal(values);
		return diag;
	}
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const nm::tybase::matrix_base<T>& mtr)
{
	auto [m, n] = mtr.size();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			out << "\t" << mtr(i, j);
		out << "\n";
	}
	out << typeid(mtr).name() << " { " << m << ", " << n << " }\n";
	return out;
}

template<typename T, typename V>
inline auto operator+(const V& val, const nm::tybase::matrix_base<T>& mtr)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, T, V>;
	return nm::tybase::matrix_base<RT>(mtr.size(), val + nm::tybase::vector_base<T>(mtr));
}

template<typename T, typename V>
inline auto operator-(const V& val, const nm::tybase::matrix_base<T>& mtr)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, T, V>;
	return nm::tybase::matrix_base<RT>(mtr.size(), val - nm::tybase::vector_base<T>(mtr));
}

template<typename T, typename V>
inline auto operator*(const V& val, const nm::tybase::matrix_base<T>& mtr)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, T, V>;
	return nm::tybase::matrix_base<RT>(mtr.size(), val * nm::tybase::vector_base<T>(mtr));
}

template<typename T, typename V>
inline auto operator/(const V& val, const nm::tybase::matrix_base<T>& mtr)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, T, V>;
	return nm::tybase::matrix_base<RT>(mtr.size(), val / nm::tybase::vector_base<T>(mtr));
}

template<typename T, typename V>
inline auto operator+(const nm::tybase::complex_base<V>& cmp, const nm::tybase::matrix_base<T>& mtr)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, nm::tybase::complex_base<T>, nm::tybase::complex_base<V>>;
	return nm::tybase::matrix_base<RT>(mtr.size(), cmp + nm::tybase::vector_base<T>(mtr));
}

template<typename T, typename V>
inline auto operator-(const nm::tybase::complex_base<V>& cmp, const nm::tybase::matrix_base<T>& mtr)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, nm::tybase::complex_base<T>, nm::tybase::complex_base<V>>;
	return nm::tybase::matrix_base<RT>(mtr.size(), cmp - nm::tybase::vector_base<T>(mtr));
}

template<typename T, typename V>
inline auto operator*(const nm::tybase::complex_base<V>& cmp, const nm::tybase::matrix_base<T>& mtr)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, nm::tybase::complex_base<T>, nm::tybase::complex_base<V>>;
	return nm::tybase::matrix_base<RT>(mtr.size(), cmp * nm::tybase::vector_base<T>(mtr));
}

template<typename T, typename V>
inline auto operator/(const nm::tybase::complex_base<V>& cmp, const nm::tybase::matrix_base<T>& mtr)
{
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, nm::tybase::complex_base<T>, nm::tybase::complex_base<V>>;
	return nm::tybase::matrix_base<RT>(mtr.size(), cmp / nm::tybase::vector_base<T>(mtr));
}

template<typename T, typename V>
inline auto operator*(const nm::tybase::vector_base<V>& vct, const nm::tybase::matrix_base<T>& mtr)
{
	assert(vct.size() == mtr.rows());
	using RT = nm::tycomp::conditional_t<nm::tycomp::is_stronger<T, V>::value, T, V>;

	nm::tybase::vector_base<RT> product(vct.size());
	for (int j = 0; j < mtr.cols(); j++)
	{
		RT sum = 0;
		for (int i = 0; i < mtr.rows(); i++)
			sum += vct[i] * mtr(i, j);
		product[j] = sum;
	}


	return product;
}
