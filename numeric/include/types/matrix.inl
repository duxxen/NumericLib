#include "matrix.hpp"
#include "../linalg/operations.hpp"

namespace nm
{
	namespace tybase
	{
		template<typename T>
		inline matrix_base<T>::matrix_base(size1D_t mn) :
			vector_base<T>(mn * mn),
			rows_(mn),
			cols_(mn)
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
			// TODO: вставьте здесь оператор return
		}

		template<typename T>
		inline void matrix_base<T>::fill_diagonal(const vector_base<T>& values, int32_t index)
		{
			// TODO: вставьте здесь оператор return
		}

		template<typename T>
		inline void matrix_base<T>::append_row(const vector_base<T>& vct)
		{
			assert(vct.size() == cols_);
			vector_base<T>::append(vct);
			rows_++;
		}

		template<typename T>
		inline void matrix_base<T>::append_col(const vector_base<T>& vct)
		{
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
		inline vector_base<T> matrix_base<T>::diagonal(int128_t i) const
		{
			return vector_base<T>();
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::slice(int32_t rbeg, int32_t rend, int32_t cbeg, int32_t cend, int32_t rstp, int32_t cstp)
		{
			
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
		inline matrix_base<T> matrix_base<T>::normalized() const
		{
			return matrix_base();
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
			return matrix_base();
		}

		template<typename T>
		inline auto matrix_base<T>::det() const
		{
		}

		template<typename T>
		inline auto matrix_base<T>::norm1() const
		{
		}

		template<typename T>
		inline auto matrix_base<T>::norm2() const
		{
		}

		template<typename T>
		inline auto matrix_base<T>::normi() const
		{
		}

		template<typename T>
		inline matrix_base<T> matrix_base<T>::operator-() const
		{
			return matrix_base();
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::dot(const matrix_base<V>& oth) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::dot(const vector_base<V>& vct) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator+(const V& value) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator-(const V& value) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator*(const V& value) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator/(const V& value) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator+(const complex_base<V>& value) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator-(const complex_base<V>& value) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator*(const complex_base<V>& value) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator/(const complex_base<V>& value) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator+(const matrix_base<V>& oth) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator-(const matrix_base<V>& oth) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator*(const matrix_base<V>& oth) const
		{
		}

		template<typename T>
		template<typename V>
		inline auto matrix_base<T>::operator*(const vector_base<V>& vct) const
		{
		}
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
}

template<typename T, typename V>
inline auto operator-(const V& val, const nm::tybase::matrix_base<T>& mtr)
{
}

template<typename T, typename V>
inline auto operator*(const V& val, const nm::tybase::matrix_base<T>& mtr)
{
}

template<typename T, typename V>
inline auto operator/(const V& val, const nm::tybase::matrix_base<T>& mtr)
{
}

template<typename T, typename V>
inline auto operator+(const nm::tybase::complex_base<V>& cmp, const nm::tybase::matrix_base<T>& mtr)
{
}

template<typename T, typename V>
inline auto operator-(const nm::tybase::complex_base<V>& cmp, const nm::tybase::matrix_base<T>& mtr)
{
}

template<typename T, typename V>
inline auto operator*(const nm::tybase::complex_base<V>& cmp, const nm::tybase::matrix_base<T>& mtr)
{
}

template<typename T, typename V>
inline auto operator/(const nm::tybase::complex_base<V>& cmp, const nm::tybase::matrix_base<T>& mtr)
{
}

template<typename T, typename V>
inline auto operator*(const nm::tybase::vector_base<V>& vct, const nm::tybase::matrix_base<T>& mtr)
{
}
