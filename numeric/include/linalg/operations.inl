#pragma once
#include "operations.hpp"

namespace nm
{
	namespace linalg
	{
		template<typename T>
		auto norm1(const tybase::vector_base<T>& vct)
		{
			return vct.norm1();
		}

		template<typename T>
		auto norm2(const tybase::vector_base<T>& vct)
		{
			return vct.norm2();
		}

		template<typename T>
		auto normi(const tybase::vector_base<T>& vct)
		{
			return vct.normi();
		}

		template<typename T>
		auto norme(const tybase::vector_base<T>& vct)
		{
			return vct.norme();
		}

		template<typename T>
		auto normp(const uint128_t& p, const tybase::vector_base<T>& vct)
		{
			return vct.normp(p);
		}

		template<typename T>
		T det(const tybase::matrix_base<T>& mtr)
		{
			return T();
		}

		template<typename T>
		T gauss_det(const tybase::matrix_base<T>& matr, bool triangle_check)
		{
			assert(matr.is_square());
			tybase::matrix_base<T> triangle(matr);

			if (triangle_check && !matr.is_triangle())
				triangle = lu(triangle).second;

			auto m = matr.rows();
			T det = 1;
			for (int i = 0; i < m; i++)
				det *= triangle(i, i);

			return det;
		}
	}

	template<typename T>
	tybase::vector_base<T> pow(const tybase::vector_base<T>& vct, float_t p)
	{
		tybase::vector_base<T> res(vct);
		for (auto& elem : res)
			elem = nm::pow(elem, p);
		return res;
	}

	template<typename T>
	tybase::matrix_base<T> pow(const tybase::matrix_base<T>& mtr, int64_t p)
	{
		if (p == 0) return identity(mtr.rows());

		auto res = p > 0 ? mtr : mtr.inversed();
		for (int i = 1; i < nm::abs(p); i++)
			res = res * res;
		return res;
	}

	template<typename T, typename V>
	auto dot(const tybase::vector_base<T>& vct1, const tybase::vector_base<V>& vct2)
	{
		vct1.dot(vct2);
	}

	template<typename T, typename V>
	auto cross(const tybase::vector_base<T>& vct1, const tybase::vector_base<V>& vct2)
	{
		return vct1.cross(vct2);
	}

	template<typename T, typename V>
	auto dot(const tybase::matrix_base<T>& mtr1, const tybase::matrix_base<V>& mtr2)
	{
		return mtr1.dot(mtr2);
	}

	template<typename T, typename V>
	auto dot(const tybase::matrix_base<T>& mtr, const tybase::vector_base<V>& vct)
	{
		return mtr.dot(vct);
	}

	template<typename T, typename V>
	auto dot(const tybase::vector_base<T>& vct, const tybase::matrix_base<V>& mtr)
	{
		return vct.dot(mtr);
	}



	template<typename T>
	inline auto tybase::matrix_base<T>::det() const
	{
		assert(is_square());
		auto& ths = *this;

		switch (rows())
		{
		case 0:	return T(0.0);
		case 1:	return ths(0, 0);
		case 2: return ths(1, 1) * ths(0, 0) - ths(1, 0) * ths(0, 1);
		case 3: return
			ths(2, 2) * ths(1, 1) * ths(0, 0)
			- ths(0, 0) * ths(1, 2) * ths(2, 1)
			- ths(0, 1) * ths(1, 0) * ths(2, 2)
			+ ths(0, 1) * ths(1, 2) * ths(2, 0)
			+ ths(0, 2) * ths(1, 0) * ths(2, 1)
			- ths(0, 2) * ths(1, 1) * ths(2, 0);

		default:
			return linalg::gauss_det(ths, true);
			break;
		}
	}
}